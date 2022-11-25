cmake_minimum_required(VERSION 3.14)

project(test)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e68764c147ea0dac1e8811925c531d937396878e.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

link_libraries(
  GTest::gtest_main
)

#--------------------

include_directories(
  "../thirdparty"
  "../server/include"
)
file(GLOB SOURCE
  "../server/src/parser/parser.cpp"
)
link_libraries(
  ${SOURCE}
)
add_subdirectory(test-server-parser)

# add_executable(
#   hello_test
#   test.cpp
# )

# gtest_discover_tests(hello_test)
