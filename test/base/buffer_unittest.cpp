#include <explore-rpc/base/buffer.h>
#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include <memory>
#include <sys/uio.h>

using namespace boost;

asio::io_service g_io_service;
std::shared_ptr<asio::ip::tcp::socket> g_tcp_socket;

/// @brief define a fixture for "BufferFunctional" suite
struct BoostTcpSocketFixture : public ::testing::Environment {

    void SetUp() override {
        g_tcp_socket.reset(new boost::asio::ip::tcp::socket(g_io_service));
        // get ip address
        asio::ip::tcp::resolver resolver(g_io_service);
        asio::ip::tcp::resolver::query query("tcpbin.com", "4242");
        auto endpoint_iterator = resolver.resolve(query);
        // connect
        g_tcp_socket->connect(*endpoint_iterator);
        std::cout << "connect success!" << std::endl; 
    }

    void TearDown() override {
        // Destroy something
        g_tcp_socket->close();
        g_tcp_socket.reset();
    }

};

TEST(BufferFunctional, TestIOFunctional) {
    std::string msg;
    msg = "test for a small amounts data!\n";
    explore::Buffer buffer;
    g_tcp_socket->write_some(asio::buffer(msg));
    boost::system::error_code ec;
    auto x = buffer.SyncRecv(*g_tcp_socket, ec);
    if (ec) {
        GTEST_FATAL_FAILURE_(ec.message().c_str());
    }
    EXPECT_STREQ("test for a small amounts data!\n", buffer.peek());
    buffer.retrieve(x);

    std::size_t sent_bytes = 0;
    msg = "test for a large mumber data!\n";
    for (int i = 0; i < 5000; i++) {
        auto x = g_tcp_socket->write_some(asio::buffer(msg));
        if (x != 0) {
            ASSERT_TRUE(true) << "peer socket queue is full!";
        }
        sent_bytes += x;
    }

    std::size_t received_bytes = 0;
    while (received_bytes < sent_bytes) {
        std::size_t n = buffer.SyncRecv(*g_tcp_socket, ec);
        received_bytes += n;
    }
    ASSERT_EQ(buffer.ReadableBytes(), sent_bytes);  // = 5000*29 = 14500
}

TEST(BufferFunctional, TestBasicFunctional) {
    explore::Buffer buffer1;
    explore::Buffer buffer2;
    buffer1.EnsureWriteableBytes(10000);
    buffer2.swap(buffer1);
    EXPECT_TRUE(buffer1.InternalCapacity() == 1024/2 && buffer2.InternalCapacity() == 10008);
    
    std::string tmp_data = "It`s a test";
    buffer1.append(tmp_data.c_str(), tmp_data.size());
    EXPECT_STREQ(buffer1.peek(), tmp_data.c_str());
    EXPECT_STREQ(buffer1.RetrieveAllAsString().c_str(), tmp_data.c_str());
    buffer1.PrependInt<uint32_t>(55U);
    EXPECT_EQ(55U, buffer1.PeekInt<uint32_t>());
    buffer1.RetrieveInt32();
    EXPECT_TRUE(buffer1.ReadableBytes() == 0);
}


int main(int argc, char** argv) {
    ::testing::AddGlobalTestEnvironment(new BoostTcpSocketFixture);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}