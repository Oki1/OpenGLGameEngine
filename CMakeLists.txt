cmake_minimum_required(VERSION 3.15)
project(OpenGLGameEngine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(dependencies)


add_executable(OpenGLGameEngine main.cpp)

target_link_libraries(OpenGLGameEngine glfw)