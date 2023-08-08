#include <explore-rpc/rpc-framework/rpcServer.h>
#include <explore-rpc/base/tcpConnection.h>
#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/buffer.h>
#include <explore-rpc/rpc-framework/rpcHeader.pb.h>
#include <explore-rpc/rpc-framework/service-discovery/ServiceDiscovery.h>
#include <google/protobuf/descriptor.h>

using namespace explore;

RpcServer::RpcServer(boost::asio::io_context& io_context, const boost::asio::ip::tcp::endpoint &addr, std::unique_ptr<detail::ServiceDiscovery>&& SD) 
    : TcpServer_(std::make_unique<base::TcpServer>(io_context, addr))
    , ServiceDiscovery_(std::move(SD))
{
    TcpServer_->SetMessageCallback(std::bind(&RpcServer::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
    TcpServer_->SetConnectCallback(std::bind(&RpcServer::HandleConnection, this, std::placeholders::_1));
    TcpServer_->SetCloseCallback(std::bind(&RpcServer::HandleClose, this, std::placeholders::_1));
    TcpServer_->SetSendCallback(std::bind(&RpcServer::HandleSend, this, std::placeholders::_1));
    TcpServer_->SetErrorCallback(std::bind(&RpcServer::HandleError, this, std::placeholders::_1, std::placeholders::_2));
}

void RpcServer::RegisterService(std::unique_ptr<Service>&& service, const std::string& provider_addr) {
    auto service_descriptor = service->GetDescriptor();
    ServiceDiscovery_->RegisterService(service_descriptor->full_name(), provider_addr);
    Services_.insert(std::make_pair(service_descriptor->full_name(), std::move(service)));
}

// total-length + service-name + method-name + request-body
bool RpcServer::HandleMessage(const base::TcpConnectionPtr& conn, Buffer* buf) {
    if (buf->ReadableBytes() < sizeof(uint32_t)) {
        conn->AsyncRecv();  // continue to receive data 
        return true;
    }
    uint32_t rpc_header_length = buf->PeekInt<uint32_t>();
    if (buf->ReadableBytes()-sizeof(uint32_t) < rpc_header_length) {
        conn->AsyncRecv();          // continue to receive data 
        return true;
    }

    explore::RpcHeader msg_header;
    bool ok = msg_header.ParseFromArray(buf->peek()+sizeof(uint32_t), rpc_header_length);
    if (!ok) {
        // FIXME: reply caller "bad rpc-header"
        return false;
    }
    
    if (buf->ReadableBytes()-rpc_header_length-sizeof(uint32_t) < msg_header.args_length()) {
        conn->AsyncRecv();
        return true;
    } else {
        buf->retrieve(rpc_header_length+sizeof(uint32_t));
    }

    auto it = Services_.find(msg_header.service_name());
    if (it == Services_.end()) {
        // FIXME: reply caller "no such service"
        return false;
    }

    const std::unique_ptr<Service>& service_instance = it->second;
    auto method_descriptor = service_instance->GetDescriptor()->FindMethodByName(msg_header.method_name()); // no need 'delete'
    
    std::unique_ptr<google::protobuf::Message> request(service_instance->GetRequestPrototype(method_descriptor).New());
    ok = request->ParseFromString(buf->RetrieveAsString(msg_header.args_length()));
    if (!ok) {
        // FIXME: reply caller "bad request"
        return false;
    }

    std::shared_ptr<google::protobuf::Message> response(service_instance->GetResponsePrototype(method_descriptor).New());

    // call local function
    service_instance->CallMethod(method_descriptor, nullptr, request.get(), response.get(), 
        google::protobuf::NewCallback<const base::TcpConnectionPtr&, std::shared_ptr<google::protobuf::Message>>(
            &RpcServer::RelpyClient, conn, response)
    );

    // if (RpcController.failed()) {
    //     return false;
    // }

    return true;
}

void RpcServer::RelpyClient(const base::TcpConnectionPtr& conn, std::shared_ptr<google::protobuf::Message> resp) {
    std::string output;
    std::cout << "--: " << conn.use_count() << std::endl;
    base::TcpConnection::BufferPtr msg = std::make_shared<Buffer>();
    if (resp->SerializeToString(&output)) {
        msg->AppendInt<uint32_t>(output.size());        // add response size
        msg->append(output.c_str(), output.size());     // add response data
        conn->AsyncSend(msg);
        /*conn->Shutdown();*/   // BUG: can`t be called immediately after AsyncSend()!!!
                            // FIXME: shoud set SendComplete() callback
    } else {
        // RpcController should set fail to notify a error occur
    }
}

bool RpcServer::HandleConnection(const base::TcpConnectionPtr& conn) {
    return true;
}

bool RpcServer::HandleClose(const base::TcpConnectionPtr& conn) {
    return true;
}

void RpcServer::HandleError(const base::TcpConnectionPtr& conn, const std::string& msg) {
    spdlog::trace("RpcServer::HandleError, error_msg: {}", msg);
}

bool RpcServer::HandleSend(const base::TcpConnectionPtr& conn) {
    return true;
}
