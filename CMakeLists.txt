cmake_minimum_required(VERSION 3.15)
project(OpenGLGameEngine)

set(CMAKE_CXX_STANDARD 14)

target_link_libraries(OpenGLGameEngine glfw)

add_executable(OpenGLGameEngine main.cpp)