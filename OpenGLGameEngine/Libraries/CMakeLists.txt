
set(LIBRARIES Camera Texture Input Shader Window VertexAttributeArray Mesh GLTFParser)

foreach(LIBNAME ${LIBRARIES})
    add_subdirectory(${LIBNAME})
endforeach()
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})