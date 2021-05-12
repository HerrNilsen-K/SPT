cmake_minimum_required(VERSION 3.17)
project(SPT)
#set(CMAKE_CXX_FLAGS "-fsanitize=address -g3")
set(CMAKE_CXX_STANDARD 17)

include_directories(SPT)

add_executable(SPT
        SPT/string.hpp
        SPT/vector.hpp
        main.cpp)
