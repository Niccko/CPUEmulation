cmake_minimum_required(VERSION 3.26)
project(CPU)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPU main.cpp
        Bus.cpp
        Bus.h
        CPU.cpp
        CPU.h

)
