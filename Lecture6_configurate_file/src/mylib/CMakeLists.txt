#we need to add library function to compiler it
message("read mylib library by cmake")
add_library(${MY_LIBRARY} SHARED mylib.cc)
target_include_directories(${MY_LIBRARY} PUBLIC 
                            "./"
                            "${CMAKE_BINARY_DIR}/configured/include") #it means relative path is same directiries


