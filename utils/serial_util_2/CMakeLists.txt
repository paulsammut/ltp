project(serial_util_2)
cmake_minimum_required(VERSION 2.8.8)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

file(GLOB myexec_SRC
    "*.h"
    "*.cpp"
)

find_package (Threads)
find_library(LIB_LOCATION serial)

add_executable(myexec ${myexec_SRC})



target_link_libraries(myexec ${LIB_LOCATION})
target_link_libraries(myexec ${CMAKE_THREAD_LIBS_INIT})

