cmake_minimum_required(VERSION 3.22)
message(STATUS "BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
project(CMakeFirstLesson 
        VERSION 1.0.0 
        LANGUAGES C CXX)   
#in this project we will use cpp17 standart
set(CMAKE_CXX_STANDARD 17)

#this is condition for cpp standart
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#we can use global variable to implementation of readable code
set(MY_LIBRARY  MyLib)
set(MY_EXECUTABLE Executable)

option(COMPILE_EXECUTABLE "Whether to compile the executable" OFF)

#we need to declare first src dir because mylib was here
add_subdirectory(src) 

if(COMPILE_EXECUTABLE)
        add_subdirectory(app)
else()
        message("W/o exe. compiling")
endif()

