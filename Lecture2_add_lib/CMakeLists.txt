# 1-)create soource and CmakeFile
# 2-)mkdir build 
# 3-)cd build 
# 4-)cmake .. Generating the build files / config the project
# 5-)cmake --build .
# 6-)./executable


cmake_minimum_required(VERSION 3.22)

project(CMakeFirstLesson 
        VERSION 1.0.0 
        LANGUAGES C CXX)   

#we need to add library
add_library(MyLib STATIC mylib.cc)

#if you want to config this file you need to target_link_libraries

add_executable(Executable main.cc)

target_link_libraries(Executable PUBLIC MyLib)  #we will link library
