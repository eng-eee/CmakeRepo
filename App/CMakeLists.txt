cmake_minimum_required(VERSION 3.22)

project(Application 
        VERSION 1.0.0 
        LANGUAGES C CXX)   

message(STATUS "BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Threads)
find_package(Boost REQUIRED COMPONENTS system)
find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
    message(STATUS "IS_CCACHE_FOUND = ${CCACHE_FOUND}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

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
option(Unit_Test_Enability "Whether to compile the executable" OFF)

add_subdirectory(include)

if(Unit_Test_Enability)
       add_subdirectory(lib/googletest)
       # add_subdirectory(test)
else()
        message("W/o exe. compiling")
endif()


target_link_libraries(${PROJECT_NAME} FileUtil TimerManager TCP_MODULE Threads::Threads ${Boost_LIBRARIES})
