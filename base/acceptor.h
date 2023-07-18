#if !defined(EXPLORE_BASE_ACCEPTOR_H)
#define EXPLORE_BASE_ACCEPTOR_H

#include <boost/asio.hpp>
#include <iostream>
#include <atomic>

namespace explore {
namespace base {

class TcpConnection;    // forward declaration

using namespace boost;

class Acceptor {
    using tcp = boost::asio::ip::tcp;

public:
    explicit Acceptor(asio::io_context& io_context, const tcp::endpoint& addr)
        : IoContext_(io_context)
        , acceptor_(IoContext_, addr, true)
        , listening_(true)
    {
        std::clog << "start listen at [" << addr << "]" << std::endl;
    }

    void Stop();

    void AsyncAccept(asio::io_context& io_context);

    void SetOnNewConnectCallback(
        const std::function<
            void(const boost::system::error_code& ec, const std::shared_ptr<TcpConnection>& connection)>& cb)
    {
        OnNewConnectCb_ = cb;
    }

private:
    asio::io_context& IoContext_;
    tcp::acceptor acceptor_;
    std::atomic<bool> listening_;
    std::function<void(const boost::system::error_code& ec, const std::shared_ptr<TcpConnection>& connection)> OnNewConnectCb_;
};

} // namespace base 
} // namespace explore 

#endif // EXPLORE_BASE_ACCEPTOR_H
