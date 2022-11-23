cmake_minimum_required(VERSION 3.0)

project(dsl_client VERSION 0.9)

set(dsl_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/include")

file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"
    "src/global.cpp"
    )

file(GLOB HEADERS
    "include/*.hpp"
    "include/**/*.hpp"
    )

file(GLOB SHARES
    "../thirdparty/plog/*.h"
    "../thirdparty/plog/**/*.h"
)


add_library(shared INTERFACE ${SHARES})
add_definitions(-DMSGPACK_NO_BOOST)

include_directories(
    "../thirdparty/msgpack-c/include"
    "../thirdparty/asio"
)

add_executable(dsl_client ${SOURCES})

target_link_libraries(dsl_client ${Boost_LIBRARIES})
target_link_libraries(dsl_client shared)

target_include_directories(dsl_client PUBLIC ${PROJECT_BINARY_DIR} "../thirdparty")
target_include_directories(dsl_client PUBLIC 
    ${PROJECT_BINARY_DIR} ${dsl_INCLUDE_DIRECTORY})