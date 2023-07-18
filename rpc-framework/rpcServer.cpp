#include <explore-rpc/rpc-framework/rpcServer.h>
#include <explore-rpc/base/tcpConnection.h>
#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/buffer.h>

using namespace explore;

RpcServer::RpcServer() {
    TcpServer_->SetMessageCallback(std::bind(&RpcServer::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
    
}

void RpcServer::Run(const int work_thread_num) {
    TcpServer_->Run(work_thread_num);
}

void RpcServer::Stop() {
    TcpServer_->Stop();
}

bool RpcServer::HandleMessage(const base::TcpConnectionPtr& conn, Buffer* buf) {
    
}

bool RpcServer::HandleConnection(const base::TcpConnectionPtr& conn) {

}

bool RpcServer::HandleClose(const base::TcpConnectionPtr& conn) {

}

void RpcServer::HandleError(const base::TcpConnectionPtr& conn, const std::string& msg) {

}

bool RpcServer::HandleSend(const base::TcpConnectionPtr& conn) {
    
}
