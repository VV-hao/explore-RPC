#include <explore-rpc/rpc-framework/service-discovery/etcdServiceDiscovery.h>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

std::string cluster_urls = "192.168.109.144:2379";
std::string service_name = "test_service";
std::string service_addr = "101.35.135.86:2379";
bool is_ready = false;

void RegisterService() {
    explore::EtcdServiceDiscovery etcd(cluster_urls, 5);
    etcd.RegisterService(service_name, service_addr);
    is_ready = true; 
    std::this_thread::sleep_for(std::chrono::seconds(10));
    etcd.RevokeLease();
    std::this_thread::sleep_for(std::chrono::seconds(7));
}

TEST(ETCD, ServiceDiscovery) {
    std::thread t([]() {
        RegisterService();
    });

    while(!is_ready) {}

    explore::EtcdServiceDiscovery etcd(cluster_urls, 0);
    auto res = etcd.Discovery(service_name);
    
    std::this_thread::sleep_for(std::chrono::seconds(6));
    ASSERT_EQ(1, res.size());
    ASSERT_STREQ(res[0].c_str(), service_addr.c_str());
    t.join();
    ASSERT_EQ(0, etcd.Discovery(service_name).size()) << "The lease does not be revoked" << std::endl;
}
