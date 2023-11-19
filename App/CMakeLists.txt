cmake_minimum_required(VERSION 3.22)

project(Application 
        VERSION 1.0.0 
        LANGUAGES C CXX)   

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS}) 
message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")

set(MAIN_FILE ${PROJECT_SOURCE_DIR}/src/main.cc)

add_executable(${PROJECT_NAME} ${MAIN_FILE})

file(GLOB_RECURSE  SOURCES 
       ${PROJECT_SOURCE_DIR}/src/cc/*.cc)

file(GLOB_RECURSE  HEADERS
       ${PROJECT_SOURCE_DIR}/src/*.h
       ${PROJECT_SOURCE_DIR}/src/h/*.h)

enable_testing ()
add_subdirectory(include)
add_subdirectory(lib/googletest)
# add_subdirectory(test)

target_link_libraries(${PROJECT_NAME} FileUtil TimerManager Threads::Threads ${Boost_LIBRARIES})
