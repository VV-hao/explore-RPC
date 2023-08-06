#if !defined(EXPLORE_RPC_FRAMEWORK_ETCD_SERVICE_DISCOVERY_H)
#define EXPLORE_RPC_FRAMEWORK_ETCD_SERVICE_DISCOVERY_H

#include <explore-rpc/rpc-framework/service-discovery/ServiceDiscovery.h>
#include <boost/noncopyable.hpp>
#include <etcd/KeepAlive.hpp>
#include <etcd/Client.hpp>
#include <memory>

namespace explore {

class EtcdServiceDiscovery final : public detail::ServiceDiscovery
                                    , boost::noncopyable {
public:
    /// @brief responsible for maintaining a connection towards an etcd server.
    /// @param etcd_urls endpoints
    /// @param ttl time-to-live of lease, if ttl = 0 means that only use Discovery
    EtcdServiceDiscovery(const std::string& etcd_urls, const int ttl);
    ~EtcdServiceDiscovery();

    /// @note only one address can be registered for a service at a time
    virtual void RegisterService(const std::string& service_name, const std::string& service_address) override;
    virtual std::vector<std::string> Discovery(const std::string& service_name) override;
    
    bool RevokeLease();

private:
    etcd::Client EtcdClient_;
    std::shared_ptr<etcd::KeepAlive> ServiceKeepAlive_;  // use lease to keep service health
};

} // namespace explore 

#endif // EXPLORE_RPC_FRAMEWORK_ETCD_SERVICE_DISCOVERY_H

