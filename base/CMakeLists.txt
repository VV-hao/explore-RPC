add_library(explore_rpc_base
    buffer.cpp
    tcpConnection.cpp
    acceptor.cpp
    tcpServer.cpp
)

target_link_libraries(explore_rpc_base spdlog::spdlog)