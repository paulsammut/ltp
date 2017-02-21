project(myfirstproj)
cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
file(GLOB myexec_SRC
    "*.h"
    "*.c"
    "*.cpp"
)

add_executable(myexec ${myexec_SRC})

