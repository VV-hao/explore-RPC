#include <explore-rpc/base/acceptor.h>
#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/tcpConnection.h>

using namespace explore::base;


TcpServer::TcpServer(const tcp::endpoint& addr)
    : IoContext_()
    , ThreadPool_()
    , acceptor_(std::make_unique<base::Acceptor>(IoContext_, addr))
{
    acceptor_->SetOnNewConnectCallback(std::bind(&TcpServer::OnNewConnect, this, std::placeholders::_1, std::placeholders::_2));
    StartAccept();   // start accept new remote connection
}

TcpServer::~TcpServer()  {
    for (auto& t : ThreadPool_) {
        t.join();
    }
}

void TcpServer::OnNewConnect(const system::error_code& ec, 
    const std::shared_ptr<base::TcpConnection>& connection)
{
    if (ec) {
        std::cerr << "accept failed: " << ec.message() << std::endl;
        return;
    }

    connection->SetConnectCallback(OnConnectCb_);
    connection->SetMessageCallback(OnMessageCb_);
    connection->SetSendCallback(OnSendCb_);
    connection->SetErrorCallback(OnErrorCb_);
    connection->SetCloseCallback(OnCloseCb_);

    if (connection->StepIntoEstablish()) {
        std::cout << "new connection from [" << connection->remote() << "] is established" << std::endl;
        connection->AsyncRecv();
    }

    StartAccept();
}

void TcpServer::Run(const int work_thread_num) {
    bool expect_val = false;
    if (!running_.compare_exchange_strong(expect_val, true)) {
        return;
    }

    Contexts_.resize(work_thread_num);
    ThreadPool_.reserve(work_thread_num);

    for (int i = 0; i < work_thread_num; i++) {
        ThreadPool_.emplace_back(
            [this, i]() {
            while (running_) {
                try {
                    Contexts_[i]->run();
                } catch(...) {
                    Contexts_[i]->restart();
                }
            }
        });
    }

    while (running_) {
        try {
            IoContext_.run();
        } catch(...) {
            IoContext_.restart();
        }
    }
}

void TcpServer::Stop() {
    bool expect_val = true;
    if (!running_.compare_exchange_strong(expect_val, false)) {
        return;
    }

    acceptor_->Stop();

    if (!Contexts_.empty()) {
        for (int i = 0; i < Contexts_.size(); i++) {
            Contexts_[i]->stop();
        }
    }
    IoContext_.stop();
}

void TcpServer::StartAccept()
{ acceptor_->AsyncAccept(GetNextContext()); }

asio::io_context& TcpServer::GetNextContext() {
    if (Contexts_.empty()) {
        return IoContext_;
    }

    auto& res = *Contexts_[NextContextId_];
    (NextContextId_ += 1) >= Contexts_.size() ? 0 : ++NextContextId_;
    return res;
}