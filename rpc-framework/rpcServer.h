#if !defined(EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H)
#define EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H

#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/callbacks.h>
#include <google/protobuf/service.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <functional>
#include <memory>

namespace explore {
namespace base {
    class TcpServer;        // forward declartaion
} // namespace base 

namespace detail {
    class ServiceDiscovery; // forward declartaion
} // namespace detail 

class RpcServer : private boost::noncopyable {
    using Service = google::protobuf::Service;
public:
    explicit RpcServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint &addr,  std::unique_ptr<detail::ServiceDiscovery>&& SD);

    inline void Run(const int work_thread_num) {
        TcpServer_->Run(work_thread_num);
    }

    inline void Stop() {
        TcpServer_->Stop();
    }

    void RegisterService(std::unique_ptr<Service>&& service, const std::string& server_addr);

private:
    bool HandleConnection(const base::TcpConnectionPtr& conn);
    bool HandleMessage(const base::TcpConnectionPtr& conn, base::Buffer* buf);
    bool HandleClose(const base::TcpConnectionPtr& conn);
    void HandleError(const base::TcpConnectionPtr& conn, const std::string& msg);
    bool HandleSend(const base::TcpConnectionPtr& conn);

    static void RelpyClient(const base::TcpConnectionPtr& conn, std::shared_ptr<google::protobuf::Message> resp);
    
private:
    std::unique_ptr<base::TcpServer> TcpServer_;
    std::unique_ptr<detail::ServiceDiscovery> ServiceDiscovery_;
    std::unordered_map<std::string, std::unique_ptr<Service>> Services_;
};

} // namespace explore 

#endif // EXPLORE_RPC_FRAMEWORK_RPC_SERVER_H
