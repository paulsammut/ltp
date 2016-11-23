project(serial_util_1)
cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lserial")
file(GLOB myexec_SRC
    "*.h"
    "*.cpp"
)

add_executable(myexec ${myexec_SRC})
