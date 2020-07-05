cmake_minimum_required(VERSION 3.15)
project(OpenGLGameEngine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../externallibs/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../externallibs/glfw/include)
target_link_libraries(OpenGLGameEngine glfw ${GLFW_LIBRARIES})
add_executable(OpenGLGameEngine main.cpp)