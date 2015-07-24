cmake_minimum_required (VERSION 2.8.11)
project (Demesne)

set(EXECUTABLE_NAME "Demesne")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)
add_subdirectory (external/libnoise)
add_subdirectory (external/gli)

include_directories(
	external/glm-0.9.7.A/
	external/glew-1.9.0/include/
	external/libnoise/src/
	external/gli/
	.
)

add_definitions(
	-DGLEW_STATIC
)

include_directories(include)
file(GLOB files src/*.cpp)
file(GLOB_RECURSE headers include/*.h)
file(GLOB_RECURSE shaders data/shaders/*)

MESSAGE( STATUS "SFML_FOUND:         " ${SFML_FOUND} )

include_directories(${SFML_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})
add_executable(${EXECUTABLE_NAME} ${files} ${headers})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARY} GLEW_190 noise)

add_custom_command( TARGET ${EXECUTABLE_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying unit test data.."
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_HOME_DIRECTORY}/data ${CMAKE_BINARY_DIR}/data
    )