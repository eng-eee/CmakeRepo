#we need to add library function to compiler it
message("read mylib library by cmake")
add_library(MyLib STATIC mylib.cc)
target_include_directories(MyLib PUBLIC "./") #it means relative path is same directiries
