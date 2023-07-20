#if !defined(EXPLORE_BASE_TCP_SERVER_H)
#define EXPLORE_BASE_TCP_SERVER_H

#include <explore-rpc/base/callbacks.h>
#include <boost/asio.hpp>
#include <vector>

namespace explore {
namespace base {

using namespace boost;

class Acceptor;         // forward declaration
class TcpConnection;    // forward declaration

/// @note use multiple loop:
/// One main-loop is responsible for accepting and dispatch new connections
/// other sub-loop is responsible for handle connection event 
/// e.g: call TcpServer::Run(3) to use one master-loop And three sub-loop
class TcpServer {
    
    using tcp = asio::ip::tcp;

public:

    /// @brief construct a tcpserver and start accept new remote connection
    explicit TcpServer(const tcp::endpoint& addr);

    void Run(const int work_thread_num);

    void Stop();

    ~TcpServer() noexcept;

    void SetConnectCallback(const OnConnectCallback_t& func)    { OnConnectCb_ = func; }
    void SetMessageCallback(const OnMessageCallback_t& func)    { OnMessageCb_ = func; }
    void SetCloseCallback(const OnCloseCallback_t& func)        { OnCloseCb_ = func; }
    void SetErrorCallback(const OnErrorCallback_t& func)        { OnErrorCb_ = func; }
    void SetSendCallback(const OnSendCallback_t& func)          { OnSendCb_ = func; }

private:
    asio::io_context& GetNextContext();

    void StartAccept();

    void OnNewConnect(const system::error_code& ec,
        const std::shared_ptr<base::TcpConnection>& connection);

private:
    asio::io_context IoContext_;                                // main-io_context
    std::unique_ptr<base::Acceptor> acceptor_;

    // for work threads
    std::vector<std::unique_ptr<asio::io_context>> Contexts_;   // sub-io_contexts
    std::vector<std::thread> ThreadPool_;
    std::atomic_bool running_ { false };
    int NextContextId_ {0};

    /// @code for behavior of tcp-connection
    OnConnectCallback_t OnConnectCb_    { nullptr };
    OnSendCallback_t    OnSendCb_       { nullptr };
    OnMessageCallback_t OnMessageCb_    { nullptr };
    OnCloseCallback_t   OnCloseCb_      { nullptr };
    OnErrorCallback_t   OnErrorCb_      { nullptr };
    /// @endcode
};

} // namespace base 
} // namespace explore 

#endif // EXPLORE_BASE_TCP_SERVER_H
