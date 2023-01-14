
#glfw
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
#target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

#glad
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)
#target_link_libraries(${PROJECT_NAME} PUBLIC Glad)

#glm
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
#target_link_libraries(${PROJECT_NAME} INTERFACE glm)
#find_package(glm REQUIRED)

#rapidjson
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/rapidjson)

#target_link_libraries(${PROJECT_NAME} glm::glm)
