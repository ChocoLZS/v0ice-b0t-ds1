file(GLOB SOURCES 
    "src/*.cpp"
    "src/**/*.cpp"
    "src/**/**/*.cpp"
    # define global variables
    "src/global.cpp"
    )

file(GLOB SUB_SHARES
    "${PROJECT_SOURCE_DIR}/thirdparty/nlohmann/nlohmann.hpp"
)
add_library(sub_shared_libs INTERFACE ${SUB_SHARES})

add_executable(${PROJECT_NAME}_server ${SOURCES})

target_link_libraries(${PROJECT_NAME}_server PRIVATE ${SHARED_LIBS} sub_shared_libs)

# server sqlite3
target_link_libraries(${PROJECT_NAME}_server LINK_PUBLIC sqlite3)

target_include_directories(${PROJECT_NAME}_server PRIVATE ${PROJECT_BINARY_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

