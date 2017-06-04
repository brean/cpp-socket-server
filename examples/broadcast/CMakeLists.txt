cmake_minimum_required (VERSION 2.8.6)
project (broadcast)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lyaml-cpp")

find_package (Threads)
add_executable(broadcast src/main.cpp)
target_link_libraries(broadcast ${CMAKE_SOURCE_DIR}/../../libsocketserverstatic.a)
