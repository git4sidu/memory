cmake_minimum_required(VERSION 3.5)

project(untitled159 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled159 main.cpp)

install(TARGETS untitled159
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
