cmake_minimum_required(VERSION 3.22)
project(lib1)

set(CMAKE_CXX_STANDARD 17)
add_library(lib1
        bitArr.cpp)

include(GoogleTest)
