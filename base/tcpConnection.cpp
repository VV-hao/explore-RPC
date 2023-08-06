#include <explore-rpc/base/tcpConnection.h>
#include <spdlog/spdlog.h>

using namespace explore::base;

bool TcpConnection::Bind(const tcp::endpoint& ep) {
    if (socket_.is_open()) {
    socket_.close();
    }
    boost::system::error_code ec;
    socket_.open(boost::asio::ip::tcp::v4(), ec);
    if (ec) {
        spdlog::error("open failed: {}", ec.message());
        return false;
    }
    socket_.bind(ep, ec);
    if (ec) {
        spdlog::error("bing failed: {}", ec.message());
        return false;
    }
    local_ = socket_.local_endpoint();
    return true;   
}

void TcpConnection::AsyncConnect(const boost::asio::ip::tcp::endpoint& remote) {
        Expire(connectTimeout_);
        socket_.async_connect(remote, 
            [self = shared_from_this()](const boost::system::error_code& ec) {
                self->Cancel(self->connectTimeout_);
                if (ec) {
                    std::cerr << "connect failed, local[" <<
                    self->socket_.local_endpoint().address().to_string() << ":" <<
                    self->socket_.local_endpoint().port() << "], remote[" <<
                    self->remote_.address().to_string() << ":" <<
                    self->remote_.port() << "]: " << ec.message() << std::endl;
                    self-> OnErrorCb_(self, "connect failed");
                    return;
                }
                self->local_    = self->socket_.local_endpoint();
                self->remote_   = self->socket_.remote_endpoint();
                self->OnConnectCb_(self);
            }
        );
    }

bool TcpConnection::SyncConnect(const boost::asio::ip::tcp::endpoint& remote) {
    boost::system::error_code ec;
    socket_.connect(remote, ec);
    if (ec) {
        std::cerr << "connect failed, local[" <<
            socket_.local_endpoint().address().to_string() << ":" <<
            socket_.local_endpoint().port() << "], remote[" <<
            remote.address().to_string() << ":" <<
            remote.port() << "]: " << ec.message() << std::endl;
        return false;
    }
    remote_ = socket_.remote_endpoint();
    local_  = socket_.local_endpoint();
    return true;
}

void TcpConnection::Close() {
    if (socket_.is_open()) {
        std::cout << "close socket, local[" <<
            local_.address() << ":" <<
            local_.port() << "], remote[" <<
            remote_.address() << ":" <<
            remote_.port() << "]." << std::endl;

        OnCloseCb_(shared_from_this());

        try {
            socket_.close();
        } catch (const boost::system::system_error& se) {
            spdlog::error("close failed: {}", se.what());
        }
    }
}

void TcpConnection::Cancel() {
    system::error_code ec;
    socket_.cancel(ec);
    if (ec) {
        spdlog::error("cancel failed: {}", ec.message());
        Close();
    }
}

bool TcpConnection::StepIntoEstablish() {
    // socket_.non_blocking(true);
    socket_.set_option(tcp::no_delay(true));
    socket_.set_option(asio::socket_base::reuse_address(true));
    local_  = socket_.local_endpoint();
    remote_ = socket_.remote_endpoint();
    if (!OnConnectCb_(shared_from_this())) {
        Close();
        return false;
    }
    return true;
}

void TcpConnection::AsyncSend(BufferPtr output_buf) {
    assert(output_buf->ReadableBytes() != 0);
    Expire(sendTimeout_);
    asio::async_write(socket_, asio::buffer(output_buf->peek(), output_buf->ReadableBytes()), 
        [self = shared_from_this(), output_buf](const boost::system::error_code& ec, std::size_t bytes_transferred) {
            self->Cancel(self->sendTimeout_);
            if (ec) {
                spdlog::error("send failed: {}", ec.message());
                self->OnErrorCb_(self, "send failed, detail: " + ec.message());
                return;
            }
            spdlog::trace("{} bytes sent.", bytes_transferred);
            output_buf->retrieve(bytes_transferred);
            if (!self->OnSendCb_(self)) {
                self->Close();
                return;
            }
            self->AsyncRecv();  // continue to receive new msg
        }
    );
}

bool TcpConnection::SyncSend(BufferPtr output_buf) {
    /// @code
    /// assert(output_buf->ReadableBytes());
    /// boost::system::error_code ec;
    /// while (output_buf->ReadableBytes()) {
    ///     size_t bytes_transferred = socket_.write_some(boost::asio::buffer(
    ///         output_buf->peek(), output_buf->ReadableBytes()), ec);
    ///     if (ec) {
    ///         std::cerr << "send failed: " << ec.message() << std::endl;
    ///         Close();
    ///         return false;
    ///     }
    ///     output_buf->retrieve(bytes_transferred);
    /// }
    /// @endcode

    // write all data in the given buffer
    assert(output_buf->ReadableBytes());
    boost::system::error_code ec;
    auto bytes_transferred = asio::write(socket_, asio::buffer(output_buf->peek(), output_buf->ReadableBytes()), ec);
    if (ec) {
        spdlog::error("send failed: {}", ec.message());
        OnErrorCb_(shared_from_this(), "send failed, detail: " + ec.message());
        return false;
    }
    spdlog::trace("{} bytes sent.", bytes_transferred);
    output_buf->retrieve(bytes_transferred);
    return true;
}

void TcpConnection::AsyncRecv() {
    Expire(recvTimeout_);
    system::error_code ec;
    inputBuf_.AsyncRecv(socket_,
        [self = shared_from_this()](const system::error_code& ec, size_t bytes_transferred) {
            self->Cancel(self->recvTimeout_);
            if (ec) {
                if (asio::error::eof == ec) {
                    self->Close();
                    return;
                }
                spdlog::error("receive failed: {}", ec.message());
                self->OnErrorCb_(self, ec.message());
                return;
            }
            spdlog::trace("{} bytes received.", bytes_transferred);
            if (!self->OnMessageCb_(self, &self->inputBuf_)) {
                self->Close();
                return;
            }
        }
    );
}

bool TcpConnection::SyncRecv() {
    system::error_code ec;
    auto bytes_transferred = inputBuf_.SyncRecv(socket_, ec);
    if (ec) {
        if (ec == asio::error::eof) {
            Close();
            return true;
        }
        OnErrorCb_(shared_from_this(), ec.message());
        spdlog::error("receive failed: {}", ec.message());
        return false;
    }
    spdlog::trace("{} bytes received.", bytes_transferred);
    if (!OnMessageCb_(shared_from_this(), &inputBuf_)) {
        Close();
        return true;
    }
    return true;
}

void TcpConnection::Expire(const std::chrono::milliseconds& timeout) {
    if (timeout > std::chrono::milliseconds::zero()) {
        timer_.expires_after(timeout);
        timer_.async_wait([self = this->shared_from_this()](const boost::system::error_code& ec) {
            if (self->timerLock_.test_and_set()) {
                return;
            }
            self->Cancel();
            self->timerLock_.clear();
        });
    }
}

void TcpConnection::Cancel(const std::chrono::milliseconds& timeout) {
    if (timeout > std::chrono::milliseconds::zero()) {
        if (timerLock_.test_and_set()) {
            return;
        }
        timer_.cancel();
        timerLock_.clear();
    }
}