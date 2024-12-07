cmake_minimum_required(VERSION 3.27)
project(fungame)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-O3)

add_executable(fungame
        source/my_math.h
        source/draw.h
        source/snake.h
        source/console.h
        source/main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
