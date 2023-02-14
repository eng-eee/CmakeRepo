#if you required add new sources or header files, you can add in "set" function
#so it is easy way to add new file and readable code

set(LIBRARY_SOURCES
    "mylib.cc")

set(LIBRARY_HEADERS
    "mylib.h")

add_library(${MY_LIBRARY} STATIC 
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS})


target_include_directories(${MY_LIBRARY} PUBLIC 
                            "./"
                            "${CMAKE_BINARY_DIR}/configured/include") #it means relative path is same directiries


##### EXAMPLE #####
# set(LIBRARY_SOURCES
#     "mylib.cc"
#     "any.cc"
#     "any.cc"
#     "any.cc")
