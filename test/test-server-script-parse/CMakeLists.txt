add_executable(
    test_server_scripts
    main.cpp
)

target_include_directories(test_server_scripts
     PUBLIC ${CMAKE_SOURCE_DIR}/include  ${CMAKE_SOURCE_DIR}/server/include)

target_link_libraries(test_server_scripts server_libs)

gtest_discover_tests(test_server_scripts)