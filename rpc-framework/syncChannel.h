#if !defined(EXPLORE_RPC_FRAMEWORK_SYNC_CHANNEL_H)
#define EXPLORE_RPC_FRAMEWORK_SYNC_CHANNEL_H

#include <explore-rpc/base/tcpConnection.h>
#include <google/protobuf/service.h>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <tuple>

namespace explore {

using namespace google;
/// @note Copyable
class SyncChannel : public google::protobuf::RpcChannel {
public:
    SyncChannel(boost::asio::io_context& driver, const std::string& server_addr)
        : IoContext_(driver)
        , ServerAddr_(server_addr)
    {}

    virtual void CallMethod(const protobuf::MethodDescriptor* method,
                          protobuf::RpcController* controller,
                          const protobuf::Message* request,
                          protobuf::Message* response,
                          protobuf::Closure* done) override;

private:
    bool DestroyConnection(const base::TcpConnectionPtr& conn) {
        auto ret = HandleClose(conn);
        auto ok = Connections_.erase(conn);
        assert(ok == 1);    (void)ok;
        return ret;
    }

    bool HandleMessage(const base::TcpConnectionPtr& conn, Buffer* buf);

    bool HandleConnection(const base::TcpConnectionPtr& conn) {
        return true;
    }

    bool HandleClose(const base::TcpConnectionPtr& conn) {
        return true;
    }

    void HandleError(const base::TcpConnectionPtr& conn, const std::string& msg) {
        spdlog::trace("SyncClient::HandleError, error_msg: {}", msg);
    }

    bool HandleSend(const base::TcpConnectionPtr& conn) {
        return true;
    }

private:
    boost::asio::io_context& IoContext_;
    const std::string ServerAddr_;

    // connection context
    using connectionCtx = std::tuple<protobuf::RpcController*, protobuf::Message*, protobuf::Closure*>;
    std::unordered_map<base::TcpConnectionPtr, connectionCtx> Connections_;
};
} // namespace explore 

#endif // EXPLORE_RPC_FRAMEWORK_SYNC_CHANNEL_H
