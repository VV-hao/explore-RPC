#if !defined(EXPLORE_RPC_FRAMEWORK_SERVICE_DISCOVERY_H)
#define EXPLORE_RPC_FRAMEWORK_SERVICE_DISCOVERY_H

#include <string>
#include <vector>

namespace explore {
namespace detail {

class ServiceDiscovery {
public:
    virtual ~ServiceDiscovery() = default;

    virtual void RegisterService(const std::string& service_name, const std::string& service_address) = 0;
    virtual std::vector<std::string> Discovery(const std::string& service_name) = 0;
};

} // namespace detail 
} // namespace explore 

#endif // EXPLORE_RPC_FRAMEWORK_SERVICE_DISCOVERY_H
