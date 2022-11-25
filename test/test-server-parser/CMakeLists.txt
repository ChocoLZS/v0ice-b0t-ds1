add_executable(
    test_server_parser
    main.cpp
)

target_include_directories(test_server_parser
     PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test_server_parser client_libs)

gtest_discover_tests(test_server_parser)