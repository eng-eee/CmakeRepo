cmake_minimum_required(VERSION 3.22)
message("STATUS: FILE_UTIL")

file(GLOB_RECURSE  SOURCES 
       ${CMAKE_CURRENT_SOURCE_DIR}/cc/*.cc)

file(GLOB_RECURSE  HEADERS
       ${CMAKE_CURRENT_SOURCE_DIR}/h/*.h)

add_library(FileUtil ${SOURCES} ${HEADERS})
target_include_directories(FileUtil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/h)
add_subdirectory(test)
