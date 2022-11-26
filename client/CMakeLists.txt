include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB SOURCES 
    "src/**/*.cpp"
    "src/global.cpp"
    )

add_library(client_libs OBJECT ${SOURCES})

add_executable(${PROJECT_NAME}_client src/main.cpp)

target_link_libraries(${PROJECT_NAME}_client PRIVATE client_libs)

target_link_libraries(${PROJECT_NAME}_client PUBLIC ${SHARED_LIBS})

target_link_libraries(${PROJECT_NAME}_client LINK_PUBLIC ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME}_client PUBLIC 
    ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)