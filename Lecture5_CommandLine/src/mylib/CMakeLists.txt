#we need to add library function to compiler it
message("read mylib library by cmake")
add_library(${MY_LIBRARY} SHARED mylib.cc)
target_include_directories(${MY_LIBRARY} PUBLIC "./") #it means relative path is same directiries
