#include <explore-rpc/base/acceptor.h>
#include <explore-rpc/base/tcpServer.h>
#include <explore-rpc/base/tcpConnection.h>
#include <spdlog/spdlog.h>

using namespace explore::base;

// helper
inline std::string ThreadIdToString(const std::thread::id& id) {
    std::ostringstream oss;
    oss << id;
    return oss.str();
}

TcpServer::TcpServer(asio::io_context& io_context, const tcp::endpoint& addr)
    : IoContext_(io_context)
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
        spdlog::error("accept failed: {}", ec.message());
        return;
    }

    connections_.insert(connection);    // add to connection-set
    connection->SetConnectCallback(OnConnectCb_);
    connection->SetMessageCallback(OnMessageCb_);
    connection->SetSendCallback(OnSendCb_);
    connection->SetErrorCallback(OnErrorCb_);
    connection->SetCloseCallback(std::bind(&TcpServer::DestroyConnection, this, std::placeholders::_1));

    if (connection->StepIntoEstablish()) {
        spdlog::info("new connection from [{0}:{1}] is established", connection->RemoteAddress().address().to_string(), connection->RemoteAddress().port());
        connection->AsyncRecv();
    }

    StartAccept();
}

void TcpServer::Run(const int work_thread_num) {
    bool expect_val = false;
    if (!running_.compare_exchange_strong(expect_val, true)) {
        return;
    }

    ThreadPool_.reserve(work_thread_num);
    Contexts_.reserve(work_thread_num);    

    for (int i = 0; i < work_thread_num; i++) {
        Contexts_.emplace_back(std::make_unique<asio::io_context>());
        ThreadPool_.emplace_back(   // sub-loop thread main func body
            [this, i]() {
            while (running_) {
                try {
                    Contexts_[i]->run();
                } catch(const std::exception& ec) {
                    spdlog::critical("in sub-loop thread {0}, boost::asio::io_context::run() throw a exception: {1}", ThreadIdToString(std::this_thread::get_id()), ec.what());
                    Contexts_[i]->restart();
                } catch(...) {
                    spdlog::critical("in sub-loop thread {}, boost::asio::io_context::run() throw a unknow exception", ThreadIdToString(std::this_thread::get_id()));
                    Contexts_[i]->restart();
                }
            }
        });
    }

    while (running_) {
        try {
            IoContext_.run();
        } catch(const std::exception& ec) {
            spdlog::critical("in sub-loop thread {0}, boost::asio::io_context::run() throw a exception: {1}", ThreadIdToString(std::this_thread::get_id()), ec.what());
            IoContext_.restart();
        } catch(...) {
            spdlog::critical("in sub-loop thread {}, boost::asio::io_context::run() throw a unknow exception", ThreadIdToString(std::this_thread::get_id()));
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