cmake_minimum_required(VERSION 3.27)

################## Top Settings ##############################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

################## Project Settings ##########################
project(stdformat
    VERSION 0.1
    LANGUAGES CXX)

################## Modal settings ##############################
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Werror -Wextra -g")
else ()
   set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O2")
   add_definitions(-DRELEASE_MODE_ON=0)
endif ()

################## Build Settings ##############################
# find_package(cpptoml REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(SFML REQUIRED system window graphics network audio)

file( GLOB_RECURSE SRC_FILES src/*.cc )
add_executable( "${PROJECT_NAME}" "src/main.cc" ${SRC_FILES} )
# target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include cpptoml_INCLUDE_DIRS)
target_include_directories(${PROJECT_NAME}
                            PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/include
                            )

target_link_libraries(${PROJECT_NAME})
# install(TARGETS YourExecutable DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/subfolder)
