#include "echoService.pb.h"
#include <explore-rpc/rpc-framework/rpcServer.h>
#include <explore-rpc/rpc-framework/service-discovery/etcdServiceDiscovery.h>
#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

class exampleServiceImpl : public example::ExampleService {
public:

    virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::example::RequestData* request,
                       ::example::ResponseData* response,
                       ::google::protobuf::Closure* done) override
    {
        auto echo_msg = request->data();
        response->set_data("[RPC] example Service#Echo: " + echo_msg);
        done->Run();
    }
};

int main() {
    spdlog::set_level(spdlog::level::trace);
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 12345);
    explore::RpcServer server(io_context, ep, std::make_unique<explore::EtcdServiceDiscovery>("192.168.109.144:2379", 5));
    server.RegisterService(std::make_unique<exampleServiceImpl>(), "192.168.109.144:12345");
    server.Run(0);
}