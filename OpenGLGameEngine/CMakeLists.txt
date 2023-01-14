cmake_minimum_required(VERSION 3.22)
project(OpenGlGameEngine)
set (CMAKE_CXX_STANDARD 20)
# Tweak information common to subcomponents
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#file(COPY ${CMAKE_BINARY_DIR}/Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add external dependencies
add_subdirectory(Sources/)
#target_include_directories(staticLibA INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
#target_include_directories(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Input/)
#target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Input/ ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Window/ ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Mesh/ ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Shader/ ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Texture/ )
add_subdirectory(ExternalLibraries/)

#target_include_directories()
#target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ExternalLibraries/glad/include)
#target_link_libraries(${PROJECT_NAME} Glad Input)

add_subdirectory(Libraries/)

#target_link_libraries(${PROJECT_NAME} ${LIBRARIES} ${EXTERNAL_LIBRARIES})

