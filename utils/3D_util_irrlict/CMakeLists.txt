cmake_minimum_required(VERSION 2.6)
PROJECT(example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++14")

FIND_PACKAGE(X11)
FIND_PACKAGE(OpenGL)
FIND_PACKAGE(ZLIB)

INCLUDE_DIRECTORIES(
    "/usr/include/"
    ${PROJECT_SOURCE_DIR}
    ${X11_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    )

FILE(GLOB SRCS 
    "*.cpp"
    "*.c"
    )
FILE(GLOB HDRS *.h)

ADD_EXECUTABLE(example
    ${SRCS}
    ${HDRS}
    )

TARGET_LINK_LIBRARIES(example
    "/usr/local/lib/libIrrlicht.a"
    ${X11_LIBRARIES}
    ${OPENGL_LIBRARIES}
    #${ZLIB_LIBRARIES}
    "/usr/lib/x86_64-linux-gnu/libXxf86vm.a"
    "/usr/lib/x86_64-linux-gnu/libXext.a"
    )


