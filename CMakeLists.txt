cmake_minimum_required(VERSION 3.28)
project(fungame)

set(CMAKE_CXX_STANDARD 26)

add_compile_options(-O3)

add_executable(fungame
        source/my_math.h
        source/draw.h
        source/snake.h
        source/console.h
        source/main.cpp
)
