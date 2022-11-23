cmake_minimum_required(VERSION 3.0)

project(dsl VERSION 0.9)

set(dsl_VERSION_MAJOR 0)
set(dsl_VERSION_MINOR 9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(dsl_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++17")

configure_file(DslConfig.h.in DslConfig.h)



file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"
    "src/**/**/*.cpp"
    # define global variables
    "src/global.cpp"
    )

file(GLOB HEADERS
    "include/*.hpp"
    "include/**/*.hpp"
    )

file(GLOB SHARES
    "../thirdparty/argparse/argparse.hpp"
    "../thirdparty/nlohmann/nlohmann.hpp"
    "../thirdparty/plog/*.h"
    "../thirdparty/plog/**/*.h"
)

add_library(argparse INTERFACE "../thirdparty/argparse/argparse.hpp")

add_library(shared INTERFACE ${SHARES})

add_library(headers INTERFACE ${HEADERS})

list(APPEND EXTRA_LIBS headers)
list(APPEND SHARED_LIBS argparse shared)

add_definitions(-DMSGPACK_NO_BOOST)

include_directories(
    "../thirdparty/msgpack-c/include"
    "../thirdparty/asio"
)

add_executable(dsl ${SOURCES})

target_link_libraries(dsl ${Boost_LIBRARIES})
target_link_libraries(dsl PUBLIC ${SHARED_LIBS})
target_link_libraries(dsl LINK_PUBLIC sqlite3)

target_include_directories(dsl PUBLIC ${PROJECT_BINARY_DIR} "../thirdparty")
target_include_directories(dsl PUBLIC ${PROJECT_BINARY_DIR} 
    ${dsl_INCLUDE_DIRECTORY}
)

target_compile_features(argparse INTERFACE cxx_std_17)

# DslConfig.h
target_include_directories(dsl PUBLIC ${PROJECT_BINARY_DIR})