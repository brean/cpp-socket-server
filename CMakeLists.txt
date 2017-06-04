cmake_minimum_required (VERSION 2.8.6)
project (socketserver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lyaml-cpp")

find_package (Threads)

# Find source files
file(GLOB SOURCES src/*.cpp)

# Create static and shared library
add_library(${PROJECT_NAME}static STATIC ${SOURCES})
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
