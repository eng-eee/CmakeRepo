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

#we need to declare first src dir because mylib was here
add_subdirectory(src) 
# And we need to declare app dir to output executable file
add_subdirectory(app)

