cmake_minimum_required(VERSION 3.22)
project(Glad)

add_library(Glad STATIC include/glad/gl.h src/gl.c)
target_include_directories(Glad PUBLIC include)