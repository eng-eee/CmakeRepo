set(EXE_SOURCES
    "main.cc")

add_executable(${MY_EXECUTABLE} ${EXE_SOURCES})
target_link_libraries(${MY_EXECUTABLE} PUBLIC ${MY_LIBRARY})  #we will link library
