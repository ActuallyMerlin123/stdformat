cmake_minimum_required(VERSION 3.12)

project(stdformat)

# set C++ std
set(CMAKE_CXX_STANDARD 20)

# source
add_executable(stdformat src/main.cc)

include_directories(src/modules)

add_library(proj SHARED src/modules/proj.cc)
target_link_libraries(stdformat proj)

set_target_properties(stdformat PROPERTIES OUTPUT_NAME "stdformat")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
