cmake_minimum_required(VERSION 3.27)
project(OpenMP_Wave_Parallel C)

set(CMAKE_C_STANDARD 23)

add_executable(OpenMP_Wave_Parallel main.c
        algorithms.h)
