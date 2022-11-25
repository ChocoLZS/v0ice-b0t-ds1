set(TEST_PREFIX test)

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



add_subdirectory(test-server-parser)

