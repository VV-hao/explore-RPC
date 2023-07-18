#if !defined(EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H)
#define EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H

#include <explore-rpc/base/callbacks.h>
#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>

namespace explore {
namespace base {
    class TcpServer;    // forward declartaion
} // namespace base 

class RpcServer : private boost::noncopyable {
public:
    explicit RpcServer();

    inline void Run(const int work_thread_num);

    inline void Stop();

private:
    bool HandleConnection(const base::TcpConnectionPtr& conn);
    bool HandleMessage(const base::TcpConnectionPtr& conn, base::Buffer* buf);
    bool HandleClose(const base::TcpConnectionPtr& conn);
    void HandleError(const base::TcpConnectionPtr& conn, const std::string& msg);
    bool HandleSend(const base::TcpConnectionPtr& conn);

    std::unique_ptr<base::TcpServer> TcpServer_;
};

} // namespace explore 

#endif // EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H
