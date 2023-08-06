#include <explore-rpc/base/tcpConnection.h>
#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/buffer.h>
#include <boost/asio.hpp>
#include <gtest/gtest.h>
#include <spdlog/logger.h>

using namespace explore::base;
using namespace boost;

struct EchoServer : public ::testing::Test {

    EchoServer() 
        : Test()
        , IoContext_()
        , Server_(IoContext_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 12345))
    {
        Server_.SetConnectCallback(std::bind(&EchoServer::HandleConnection, this, std::placeholders::_1));
        Server_.SetMessageCallback(std::bind(&EchoServer::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
        Server_.SetSendCallback(std::bind(&EchoServer::HandleSend, this, std::placeholders::_1));
        Server_.SetErrorCallback(std::bind(&EchoServer::handleError, this, std::placeholders::_1, std::placeholders::_2));
        Server_.SetCloseCallback(std::bind(&EchoServer::handleClose, this, std::placeholders::_1));
    }

    virtual void SetUp() override {
        spdlog::set_level(spdlog::level::trace);
    }

    bool HandleConnection(const TcpConnectionPtr& conn) {
        return true;
    }

    bool handleClose(const TcpConnectionPtr& conn) {
        spdlog::debug("HandleClose is called");
        return true;
    }

    void handleError(const TcpConnectionPtr& conn, const std::string& msg) {
        spdlog::debug("HandleError is called");
    }

    bool HandleMessage(const TcpConnectionPtr& conn, Buffer* buf) {
        auto data = buf->RetrieveAllAsString();
        auto output_buf = std::make_shared<Buffer>();
        output_buf->append(data.c_str(), data.size());

        conn->AsyncSend(output_buf);
        return true;
    }

    bool HandleSend(const TcpConnectionPtr& conn) {
        static int count = 0;   // send 5 times stop service
        if (++count == 5) {
            Server_.Stop();
        }
        return true;
    }

    boost::asio::io_context IoContext_;
    TcpServer Server_;
};

TEST_F(EchoServer, SingleLoop) {
    Server_.Run(0);
}

// one master loop And three sub loop
TEST_F(EchoServer, MultiLoop) {
    Server_.Run(3);
}