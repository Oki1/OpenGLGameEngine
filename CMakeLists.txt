cmake_minimum_required(VERSION 3.15)
project(OpenGLGameEngine)

set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES main.cpp GLAD/src/glad.c)

add_subdirectory(dependencies)

include_directories(GLAD/include)

add_executable(OpenGLGameEngine ${SOURCE_FILES})

target_link_libraries(OpenGLGameEngine glfw)