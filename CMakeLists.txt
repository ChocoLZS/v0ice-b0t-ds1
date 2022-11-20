cmake_minimum_required(VERSION 3.0)

project(dsl VERSION 0.1)

set(dsl_VERSION_MAJOR 0)
set(dsl_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(dsl_INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/include")

configure_file(DslConfig.h.in DslConfig.h)

file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"

    "src/interpreter/*.cpp"
    # define global variables
    "src/global.cpp"
    )

file(GLOB HEADERS
    "include/*.hpp"
    "include/**/*.hpp"
    "include/interpreter/*.hpp"
    )

add_library(argparse INTERFACE "include/argparse/argparse.hpp")
add_library(headers INTERFACE ${HEADERS})

list(APPEND EXTRA_LIBS headers argparse)

add_executable(dsl ${SOURCES})



target_link_libraries(dsl PUBLIC ${EXTRA_LIBS})
target_link_libraries(dsl LINK_PUBLIC sqlite3)
target_include_directories(dsl PUBLIC ${PROJECT_BINARY_DIR} ${dsl_INCLUDE_DIRECTORY})
target_compile_features(argparse INTERFACE cxx_std_17)

# DslConfig.h
target_include_directories(dsl PUBLIC ${PROJECT_BINARY_DIR})