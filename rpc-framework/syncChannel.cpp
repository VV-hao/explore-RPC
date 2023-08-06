#include <explore-rpc/rpc-framework/syncChannel.h>
#include <explore-rpc/rpc-framework/rpcHeader.pb.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <memory>

using namespace explore;

void SyncChannel::CallMethod(const protobuf::MethodDescriptor* method,
                          protobuf::RpcController* controller,
                          const protobuf::Message* request,
                          protobuf::Message* response,
                          protobuf::Closure* done)
{
    base::TcpConnectionPtr conn = std::make_shared<base::TcpConnection>(IoContext_);
    if (!conn->SyncConnect(ServerAddr_)) {
        if (controller)
            controller->SetFailed("Failed to connect target server");
        return;
    }

    protobuf::RpcController* saveController = controller;
    protobuf::Message* saveResponse = response;
    protobuf::Closure* saveCallback = done;
    auto context = std::make_tuple<protobuf::RpcController*, protobuf::Message*, protobuf::Closure*>(std::move(saveController), std::move(response), std::move(done));
    auto pair = std::make_pair<const base::TcpConnectionPtr, connectionCtx>(base::TcpConnectionPtr(conn), std::move(context));
    Connections_.insert(pair);
    conn->SetMessageCallback(std::bind(&SyncChannel::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
    conn->SetConnectCallback(std::bind(&SyncChannel::HandleConnection, this, std::placeholders::_1));
    conn->SetCloseCallback(std::bind(&SyncChannel::HandleClose, this, std::placeholders::_1));
    conn->SetSendCallback(std::bind(&SyncChannel::HandleSend, this, std::placeholders::_1));
    conn->SetErrorCallback(std::bind(&SyncChannel::HandleError, this, std::placeholders::_1, std::placeholders::_2));

    auto service_name = method->service()->full_name();
    auto method_name = method->name();
    uint32_t args_length = static_cast<uint32_t>(request->ByteSizeLong());

    RpcHeader header;
    header.set_service_name(service_name);
    header.set_method_name(method_name);
    header.set_args_length(args_length);
    std::string output_data = header.SerializeAsString() + request->SerializeAsString();

    base::TcpConnection::BufferPtr output_buf = std::make_shared<explore::base::Buffer>();
    output_buf->AppendInt<uint32_t>(static_cast<uint32_t>(header.ByteSizeLong()));
    output_buf->append(output_data.c_str(), output_data.size());

    auto ok = conn->SyncSend(std::move(output_buf));
    if (!ok) {
        if (controller)
            controller->SetFailed("Failed to send request to server");
        return;
    }

    while (!conn->SyncRecv()) {}
}

bool SyncChannel::HandleMessage(const base::TcpConnectionPtr& conn, Buffer* buf) {
    if (buf->ReadableBytes() < sizeof(uint32_t)) {
        return false;
    }
    
    auto length = buf->PeekInt<uint32_t>();
    if (buf->ReadableBytes()-sizeof(uint32_t) < length) {
        return false;
    } else {
        buf->retrieve(sizeof(uint32_t));
    }

    protobuf::RpcController* controller = std::get<0>(Connections_[conn]);
    protobuf::Message* response         = std::get<1>(Connections_[conn]);
    protobuf::Closure* done             = std::get<2>(Connections_[conn]);

    auto msg = buf->RetrieveAsString(length);
    bool ok = response->ParseFromString(msg);
    if (!ok) {  
        if (controller)
            controller->SetFailed("Failed to parse server response");
        return true;
    }

    if (done)
        done->Run();

    return true;
}
