#include <explore-rpc/rpc-framework/syncChannel.h>
#include <explore-rpc/rpc-framework/service-discovery/etcdServiceDiscovery.h>
#include "echoService.pb.h"
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;
    explore::SyncChannel channel(io_context, "192.168.109.144:12345");

    example::ExampleService::Stub stub_service(&channel);
    example::RequestData request;
    example::ResponseData response;
    request.set_data("hello");
    stub_service.Echo(nullptr, &request, &response, google::protobuf::NewCallback<example::ResponseData&>(
        [](example::ResponseData& resp) { std::cout << resp.data() << std::endl; }, response));

    io_context.run();
}