file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"
    "src/global.cpp"
    )

add_executable(${PROJECT_NAME}_client ${SOURCES})

target_link_libraries(${PROJECT_NAME}_client ${SHARED_LIBS})

target_include_directories(${PROJECT_NAME}_client PUBLIC 
    ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)