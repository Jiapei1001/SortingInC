cmake_minimum_required(VERSION 3.16)
project(hw04_Heapsort C)

set(CMAKE_C_STANDARD 99)

add_executable(hw04_Heapsort main.c a4_heapsort/min_heap_int/min_heap_int.h a4_heapsort/min_heap_int/min_heap_run.c)