cmake_minimum_required(VERSION 3.17)
project(SPT)

set(CMAKE_CXX_STANDARD 14)

include_directories(SPT)

add_executable(SPT
        SPT/string.hpp
        SPT/vector.hpp
        main.cpp)
