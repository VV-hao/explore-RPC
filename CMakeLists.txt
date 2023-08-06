cmake_minimum_required(VERSION 3.5)

project(explore-RPC)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/..)

find_package(spdlog REQUIRED)
if(spdlog_FOUND)
    MESSAGE(STATUS "Found package 'spdlog': ${spdlog_DIR}")
endif(spdlog_FOUND)

add_subdirectory(${CMAKE_SOURCE_DIR}/base)
add_subdirectory(${CMAKE_SOURCE_DIR}/rpc-framework)
add_subdirectory(${CMAKE_SOURCE_DIR}/bad-try)

set(BUILD_UNIT_TEST ON)
if(${BUILD_UNIT_TEST})
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif(${BUILD_UNIT_TEST})
