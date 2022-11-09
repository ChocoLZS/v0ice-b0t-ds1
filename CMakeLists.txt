cmake_minimum_required(VERSION 3.0)

project(dsl)

file(GLOB SOURCES "src/*.cpp")

include_directories(include)

add_executable(dsl ${SOURCES})