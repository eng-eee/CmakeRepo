set(test_target "TimerManagerTest")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc)

set(SOURCES ${TEST_SOURCES})

add_executable(${test_target} ${TEST_SOURCES})

add_test(NAME ${test_target} COMMAND ${test_target})

target_link_libraries(${test_target} PUBLIC TimerManager gtest)