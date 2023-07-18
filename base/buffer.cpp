#include <explore-rpc/base/buffer.h>

using namespace explore::base;

// define static data member

const char Buffer::kCrlf[] = "\r\n";
const std::size_t Buffer::kInitialSize;
const std::size_t Buffer::kCheapPrepend;

// end define static data member



// define member function

void Buffer::MakeSpace(const std::size_t target_len) {
    if (PrependableBytes() + WriteableBytes() < target_len + kCheapPrepend) {
        buf_.resize(writeIndex_+target_len);
    } else {
        assert(readIndex_ > kCheapPrepend);
        std::size_t readable_bytes = ReadableBytes();
        std::move(begin()+readIndex_, begin()+writeIndex_, begin()+kCheapPrepend);
        readIndex_  = kCheapPrepend;
        writeIndex_ = kCheapPrepend + readable_bytes; 
        assert(readable_bytes == ReadableBytes());
    }
}

std::size_t Buffer::SyncRecv(boost::asio::ip::tcp::socket& sock, system::error_code& ec) {
    // when there is enough space in this buffer, don't read into extrabuf.
    // when extrabuf is used, we read 128k bytes at most.
    char extra_buf[1024*128];
    std::array<boost::asio::mutable_buffer, 2> buffers;
    std::size_t writeable_bytes = WriteableBytes();
    buffers[0] = boost::asio::mutable_buffer(BeginWrite(), writeable_bytes);
    buffers[1] = boost::asio::mutable_buffer(extra_buf, sizeof extra_buf);
    std::size_t transmit_bytes = sock.read_some(buffers, ec);    
    if (transmit_bytes <= writeable_bytes) {
        writeIndex_ += transmit_bytes;
    } else {
        writeIndex_ = buf_.size();
        append(extra_buf, transmit_bytes-writeable_bytes);
    }
    return transmit_bytes;
}

void Buffer::AsyncRecv(boost::asio::ip::tcp::socket& sock, const std::function<void(const system::error_code& ec, std::size_t bytes_transferred)>& cb) {
    // when there is enough space in this buffer, don't read into extrabuf.
    // when extrabuf is used, we read 128k bytes at most.
    char extra_buf[1024*128];
    std::array<boost::asio::mutable_buffer, 2> buffers;
    std::size_t writeable_bytes = WriteableBytes();
    buffers[0] = boost::asio::mutable_buffer(BeginWrite(), writeable_bytes);
    buffers[1] = boost::asio::mutable_buffer(extra_buf, sizeof extra_buf);
    auto buffer_cb = 
        [this, cb, &extra_buf, writeable_bytes](const system::error_code& ec, std::size_t bytes_transferred) {
            if (bytes_transferred <= writeable_bytes) {
                this->writeIndex_ += bytes_transferred;
            } else {
                this->writeIndex_ = this->buf_.size();
                this->append(extra_buf, bytes_transferred-writeable_bytes);
            }
            cb(ec, bytes_transferred);  // call user special callback
        }; 

    sock.async_read_some(buffers, buffer_cb);
}

// end define member function