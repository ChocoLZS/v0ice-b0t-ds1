add_executable(
    test_server_parser
    main.cpp
)

target_include_directories(
    test_server_parser 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

gtest_discover_tests(test_server_parser)