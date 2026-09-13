cmake_minimum_required(VERSION 4.3)
project(untitled C)
add_compile_options(-mavx2)
set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        simd.c
        cpu.c
        header.h
)
