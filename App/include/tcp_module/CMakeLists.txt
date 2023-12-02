cmake_minimum_required(VERSION 3.22)
message(STATUS  "TCP-LIB")

file(GLOB_RECURSE  SOURCES 
       ${CMAKE_CURRENT_SOURCE_DIR}/cc/*.cc)

file(GLOB_RECURSE  HEADERS
       ${CMAKE_CURRENT_SOURCE_DIR}/h/*.h)

add_library(TCP_MODULE ${SOURCES} ${HEADERS})
target_include_directories(TCP_MODULE PUBLIC STATIC ${CMAKE_CURRENT_SOURCE_DIR}/h)
add_subdirectory(test)
