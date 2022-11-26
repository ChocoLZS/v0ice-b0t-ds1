include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

file(GLOB SOURCES 
    "src/**/*.cpp"
    "src/**/**/*.cpp"
    # define global variables
    "src/global.cpp"
    )

add_library(server_libs OBJECT ${SOURCES})

add_executable(${PROJECT_NAME}_server src/main.cpp)

target_link_libraries(${PROJECT_NAME}_server PRIVATE server_libs)

target_link_libraries(${PROJECT_NAME}_server PUBLIC ${SHARED_LIBS})
# server sqlite3
target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC sqlite3)

target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC ${Boost_LIBRARIES})
# for clangd to work ? maybe...
target_include_directories(${PROJECT_NAME}_server PUBLIC 
    ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)


