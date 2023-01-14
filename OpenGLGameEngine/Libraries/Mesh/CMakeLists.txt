cmake_minimum_required(VERSION 3.22)
set(SOURCE_FILES Mesh.cpp)
project(Mesh)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/Headers)

target_link_libraries(${PROJECT_NAME} PUBLIC glm Shader VertexAttributeArray Texture)