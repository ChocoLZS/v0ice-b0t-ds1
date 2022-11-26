add_executable(
    test_string
    main.cpp
)

target_include_directories(test_string
     PUBLIC ${CMAKE_SOURCE_DIR}/include  ${CMAKE_SOURCE_DIR}/server/include)

target_link_libraries(test_string server_libs)

gtest_discover_tests(test_string)