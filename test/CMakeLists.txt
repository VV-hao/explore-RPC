find_library(GTest_LIBRARIES gtest)
find_library(GTest_MAIN gtest_main)

message(STATUS "Variable GTest_LIBRARIES: ${GTest_LIBRARIES}")
message(STATUS "Variable GTest_MAIN: ${GTest_MAIN}")
message(STATUS "Start build unit test files")


add_executable(buffer_unittest base/buffer_unittest.cpp)
target_link_libraries(buffer_unittest ${GTest_MAIN} ${GTest_LIBRARIES} explore_rpc_base pthread)

add_executable(tcpConnection_unittest base/tcpConnection_unittest.cpp)
target_link_libraries(tcpConnection_unittest explore_rpc_base pthread)
