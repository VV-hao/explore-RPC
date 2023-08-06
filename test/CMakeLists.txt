find_library(GTest_LIBRARIES gtest)
find_library(GTest_MAIN gtest_main)

message(STATUS "Variable GTest_LIBRARIES: ${GTest_LIBRARIES}")
message(STATUS "Variable GTest_MAIN: ${GTest_MAIN}")
message(STATUS "Start build unit test files")

add_executable(buffer_unittest base/buffer_unittest.cpp)
target_link_libraries(buffer_unittest ${GTest_MAIN} ${GTest_LIBRARIES} explore_rpc_base pthread)

add_executable(tcpConnection_unittest base/tcpConnection_unittest.cpp)
target_link_libraries(tcpConnection_unittest explore_rpc_base pthread ${GTest_MAIN} ${GTest_LIBRARIES})

add_executable(tcpServer_unittest base/tcpServer_unittest.cpp)
target_link_libraries(tcpServer_unittest explore_rpc_base ${GTest_MAIN} ${GTest_LIBRARIES} spdlog::spdlog)

add_executable(etcd_unittest rpc-framework/etcdSD_unittest.cpp)
target_link_libraries(etcd_unittest explore_rpc_framework ${GTest_MAIN} ${GTest_LIBRARIES} pthread)

add_executable(echo_service rpc-framework/echo/echoService.pb.cc rpc-framework/echo/server.cpp)
target_link_libraries(echo_service explore_rpc_framework)

add_executable(rpc-client rpc-framework/echo/echoService.pb.cc rpc-framework/echo/asyncClient.cpp)
target_link_libraries(rpc-client explore_rpc_framework)