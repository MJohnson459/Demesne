cmake_minimum_required (VERSION 2.8.11)
project (Demesne)

set(EXECUTABLE_NAME "Demesne")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(include)
file(GLOB files src/*.cpp)
file(GLOB_RECURSE headers include/*.h)

MESSAGE( STATUS "SFML_FOUND:         " ${SFML_FOUND} )
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  add_executable(${EXECUTABLE_NAME} ${files} ${headers})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
  
endif()