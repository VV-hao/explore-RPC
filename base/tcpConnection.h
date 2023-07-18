#if !defined(EXPLORE_BASE_TCP_CONNECTION_HPP)
#define EXPLORE_BASE_TCP_CONNECTION_HPP

#include <explore-rpc/base/callbacks.h>
#include <explore-rpc/base/buffer.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <type_traits>
#include <iostream>
#include <memory>
#include <any>

namespace explore {
namespace base {

using boost::asio::ip::tcp;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
                    , private boost::noncopyable {
public:
    using TcpConnPtr    = std::shared_ptr<TcpConnection>;
    using BufferPtr     = std::shared_ptr<Buffer>;
    using BufferWeakPtr = std::weak_ptr<Buffer>;


    TcpConnection(boost::asio::io_service& io_service, std::any server = nullptr)
        : ioService_(io_service)
        , server_(server)
        , socket_(io_service)
        , local_()
        , remote_()
        , inputBuf_()
        , timer_(ioService_)
    {

    }

    bool Bind(const tcp::endpoint& ep);

    void AsyncConnect(const boost::asio::ip::tcp::endpoint& remote);

    void AsyncConnect(const std::string& host, unsigned short port)
    { AsyncConnect(tcp::endpoint(asio::ip::address::from_string(host), port)); }

    bool SyncConnect(const boost::asio::ip::tcp::endpoint& remote);

    bool SyncConnect(const std::string& host, unsigned short port)
    { return SyncConnect(tcp::endpoint(asio::ip::address::from_string(host), port)); }

    void Close();

    /// @brief cancel all pending async operation of socket 
    void Cancel();

    bool StepIntoEstablish();

    void AsyncSend(BufferPtr output_buf);

    bool SyncSend(BufferPtr output_buf);

    void AsyncRecv();

    bool SyncRecv();


    boost::asio::io_service& IoService() 
    { return static_cast<asio::io_service&>(socket_.get_executor().context()); }

    tcp::socket& Socket() { return socket_; }

    void SetTimeout(const std::chrono::milliseconds& connect_timeout, const std::chrono::milliseconds& send_timeout,
        const std::chrono::milliseconds& receive_timeout)
    {
        connectTimeout_ = connect_timeout;
        sendTimeout_    = send_timeout;
        recvTimeout_    = receive_timeout;
    }

    tcp::endpoint remote() const
    { return remote_; }
    
    void SetConnectCallback(const OnConnectCallback_t& func)    { OnConnectCb_ = func; }
    void SetMessageCallback(const OnMessageCallback_t& func)    { OnMessageCb_ = func; }
    void SetCloseCallback(const OnCloseCallback_t& func)        { OnCloseCb_ = func; }
    void SetErrorCallback(const OnErrorCallback_t& func)        { OnErrorCb_ = func; }
    void SetSendCallback(const OnSendCallback_t& func)          { OnSendCb_ = func; }

private:
    void Expire(const std::chrono::milliseconds& timeout);

    /// @brief Cancel async operation of timer 
    void Cancel(const std::chrono::milliseconds& timeout);

private:
    boost::asio::io_service& ioService_;
    std::any server_;
    tcp::socket socket_;
    tcp::endpoint local_, remote_;
    Buffer inputBuf_;
    boost::asio::steady_timer timer_;
    std::chrono::milliseconds connectTimeout_, sendTimeout_, recvTimeout_;  // for cancel pending asynchronous operations.
    std::atomic_flag timerLock_ { ATOMIC_FLAG_INIT };

    /// @code Object-Based
    OnConnectCallback_t OnConnectCb_;
    OnSendCallback_t    OnSendCb_;
    OnMessageCallback_t OnMessageCb_;
    OnCloseCallback_t   OnCloseCb_;
    OnErrorCallback_t   OnErrorCb_;
    /// @endcode
};

} // namespace base 
} // namespace explore

#endif // EXPLORE_BASE_TCP_CONNECTION_HPP
