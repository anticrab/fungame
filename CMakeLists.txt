cmake_minimum_required(VERSION 3.28)
project(fungame)

set(CMAKE_CXX_STANDARD 26)

add_executable(fungame
        source/my_math.h
        source/geometry.h
        source/console.h
        source/main.cpp
)
