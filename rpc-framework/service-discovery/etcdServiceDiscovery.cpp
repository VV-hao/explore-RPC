#include <explore-rpc/rpc-framework/service-discovery/etcdServiceDiscovery.h>
#include <spdlog/spdlog.h>

using namespace explore;

EtcdServiceDiscovery::EtcdServiceDiscovery(const std::string& etcd_urls, const int ttl)
    : EtcdClient_(etcd_urls)
    , ServiceKeepAlive_()
{
    if (ttl > 0) {
        ServiceKeepAlive_ = EtcdClient_.leasekeepalive(ttl).get();
    }
}

EtcdServiceDiscovery::~EtcdServiceDiscovery() = default;

void EtcdServiceDiscovery::RegisterService(const std::string& service_name, const std::string& service_address) {
    std::string key = "/" + service_name + "/" + service_address; 
    try {
        etcd::Response response = EtcdClient_.set(key, "alive", ServiceKeepAlive_->Lease()).get();
        if (response.is_ok()) {
            spdlog::info("registered service '{}' success.", service_name); 
        } else {
            spdlog::error("registered service '{}' fail, detail: {}", service_name, response.error_message());
        }
    } catch(const pplx::task_canceled& ec) {
        spdlog::error("communication problem, details: {}", ec.what());
    } catch(const std::exception& ec) {
        spdlog::error("unknow exception, detail: {}", ec.what());
    }
}

std::vector<std::string> EtcdServiceDiscovery::Discovery(const std::string& service_name) {
    std::string directory_node = "/" + service_name + "/";
    etcd::Response response = EtcdClient_.ls(directory_node).get();
    if (response.is_ok()) {
        try {
            std::vector<std::string> addresses;
            for (int i = 0; i < response.keys().size(); i++) {
                addresses.emplace_back(response.key(i).substr(directory_node.size()));
            }
            return addresses;
        } catch(const pplx::task_canceled& ec) {
            spdlog::error("communication problem, details: {}", ec.what());
        } catch(const std::exception& ec) {
            spdlog::error("unknow exception, detail: {}", ec.what());
        }
    } else {
        spdlog::error("discovered serivce {} fail, detail: {}", service_name, response.error_message());
    }
    return {};
}

bool EtcdServiceDiscovery::RevokeLease() { 
    auto resp = EtcdClient_.leaserevoke(ServiceKeepAlive_->Lease()).get();
    if (resp.is_ok()) {
        ServiceKeepAlive_.reset();
        return true;
    }
    spdlog::error("revoke lease fail, detail: {}", resp.error_message());
    return false;
}