cmake_minimum_required(VERSION 3.22)
message(STATUS "BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
project(CMakeConfig 
        VERSION 1.0.0 
        LANGUAGES C CXX)   

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MY_LIBRARY  MyLib)
set(MY_EXECUTABLE Executable)

option(COMPILE_EXECUTABLE "Whether to compile the executable" OFF)

add_subdirectory(configured)
add_subdirectory(src) 
if(COMPILE_EXECUTABLE)
        add_subdirectory(app)
else()
        message("W/o exe. compiling")
endif()

