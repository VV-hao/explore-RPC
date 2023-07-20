add_library(explore_rpc_framework
    rpcServer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/service-discovery/etcdServiceDiscovery.cpp
)

find_package(etcd-cpp-api REQUIRED)
if(etcd-cpp-api_FOUND)
    target_link_libraries(explore_rpc_framework etcd-cpp-api)
endif(etcd-cpp-api_FOUND)
