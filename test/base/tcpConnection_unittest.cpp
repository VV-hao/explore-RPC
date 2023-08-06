#include <explore-rpc/base/tcpConnection.h>
#include <explore-rpc/base/callbacks.h>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

using namespace explore::base;
std::string msg = "hello\n";

boost::asio::io_context g_io_context;

TEST(TcpConnection, TestSyncFunc) {
    spdlog::set_level(spdlog::level::trace);
    TcpConnection connection(g_io_context);
    
    asio::ip::tcp::resolver resolver(g_io_context);
    asio::ip::tcp::endpoint echo_server_address
         = *resolver.resolve(asio::ip::tcp::resolver::query("tcpbin.com", "4242"));
    asio::ip::tcp::endpoint local_address(asio::ip::tcp::v4(), 12345);
    connection.Bind(local_address);
    ASSERT_TRUE(connection.SyncConnect(echo_server_address));

    spdlog::info("local address: [{0}:{1}] peer address: [{2}{3}]", 
        connection.LocalAddress().address().to_string(), connection.LocalAddress().port(),
        connection.RemoteAddress().address().to_string(), connection.RemoteAddress().port());

    TcpConnection::BufferPtr buf = std::make_shared<Buffer>();
    buf->append(msg.c_str(), msg.size());
    ASSERT_TRUE(connection.SyncSend(buf));
    ASSERT_TRUE(connection.SyncRecv());
}

TEST(TcpConnection, TestAsyncFunc) {
    spdlog::set_level(spdlog::level::trace);
    TcpConnectionPtr connection = std::make_shared<TcpConnection>(g_io_context);

    asio::ip::tcp::resolver resolver(g_io_context);
    asio::ip::tcp::endpoint echo_server_address
         = *resolver.resolve(asio::ip::tcp::resolver::query("tcpbin.com", "4242"));

    connection->SetConnectCallback([](const TcpConnectionPtr& conn)->bool {
        spdlog::info("local address: [{0}:{1}] peer address: [{2}{3}]", 
            conn->LocalAddress().address().to_string(), conn->LocalAddress().port(),
            conn->RemoteAddress().address().to_string(), conn->RemoteAddress().port());
        return true;
    });
    connection->AsyncConnect(echo_server_address);
    
    TcpConnection::BufferPtr buf = std::make_shared<Buffer>();
    buf->append(msg.c_str(), msg.size());

    connection->SetMessageCallback([](const TcpConnectionPtr& conn, Buffer* buf)->bool {
        EXPECT_EQ(msg.size(), buf->ReadableBytes());
        EXPECT_STREQ(buf->RetrieveAllAsString().c_str(), msg.c_str());
        g_io_context.stop();
        return true;
    });

    connection->SetCloseCallback([](const TcpConnectionPtr& conn)->bool {
        spdlog::info("connection [{0}:{1}] is closed", conn->LocalAddress().address().to_string(), conn->LocalAddress().port());
        return true;
    });

    connection->SetSendCallback([](const TcpConnectionPtr& conn)->bool {
        return true;
    });

    connection->AsyncSend(buf);

    g_io_context.run();
}