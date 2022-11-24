cmake_minimum_required(VERSION 3.0)

project(dsl VERSION 1.0)

set(SERVER_VERSION_MAJOR 1)
set(SERVER_VERSION_MINOR 0)

set(CLIENT_VERSION_MAJOR 1)
set(CLIENT_VERSION_MINOR 0)

configure_file(DslConfig.h.in DslConfig.h)

# DslConfig.h
include_directories(${PROJECT_BINARY_DIR})

# c++17标准 for json std::optional
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# 共用第三方库，不需要额外配置的单文件库
file(GLOB SHARES
    "${PROJECT_SOURCE_DIR}/thirdparty/plog/*.h"
    "${PROJECT_SOURCE_DIR}/thirdparty/plog/**/*.h"
)

add_library(argparse INTERFACE "${PROJECT_SOURCE_DIR}/thirdparty/argparse/argparse.hpp")
add_library(shared INTERFACE ${SHARES})
list(APPEND SHARED_LIBS argparse shared)

add_definitions(-DMSGPACK_NO_BOOST)

include_directories(
    "${PROJECT_SOURCE_DIR}/thirdparty/msgpack-c/include"
    "${PROJECT_SOURCE_DIR}/thirdparty/asio"
    "${PROJECT_SOURCE_DIR}/thirdparty"
)

link_libraries(${Boost_LIBRARIES})
target_compile_features(argparse INTERFACE cxx_std_17)

add_subdirectory(client)
add_subdirectory(server)
