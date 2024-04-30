cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(tarotserver)
file(GLOB_RECURSE SRC_FILES src/*.cpp)


add_executable(tarotserver ${SRC_FILES})
target_include_directories(tarotserver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/libs ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.h ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tarotserver jsoncpp curl)