cmake_minimum_required(VERSION 4.3.0)

project(Socket)
add_executable(Main)
target_sources(Main
    PRIVATE
        main.cpp
)

add_library(Socket)
target_sources(Socket
    PRIVATE
        Socket.cpp

    PUBLIC
        FILE_SET HEADERS
        FILES
            Socket.h
)

target_link_libraries(Main
    PRIVATE
        Socket
)
