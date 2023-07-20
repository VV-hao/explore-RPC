 #include <explore-rpc/base/acceptor.h>
#include <explore-rpc/base/tcpConnection.h>

using namespace explore::base;

void Acceptor::Stop() {
    bool expect_status = true;
    if (listening_.compare_exchange_strong(expect_status, false)) { // Compare-and-Swap
        acceptor_.cancel();
        acceptor_.close();
    }
}

void Acceptor::AsyncAccept(asio::io_context& io_context) {
    std::shared_ptr<TcpConnection> connection = std::make_shared<TcpConnection>(io_context);
    acceptor_.async_accept(connection->Socket(), 
        [this, conn = connection](const boost::system::error_code& ec) {
             OnNewConnectCb_(ec, std::move(conn));
        }
    );
}