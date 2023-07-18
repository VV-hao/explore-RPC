#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/tcpConnection.h>
#include <explore-rpc/bad-try/buffer.hpp>
#include <boost/asio/thread_pool.hpp>
#include <iostream>

void myTask() {
    std::cout << "Task executed in thread: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(10));
}

int main() {
    using namespace explore::base;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("192.168.109.144"), 12345);
    TcpServer server(ep);
    server.Run(0);
    std::cout << "end..." << std::endl;
}
