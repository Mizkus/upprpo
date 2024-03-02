enable_testing()

add_executable(test test.cpp)

target_link_libraries(test lib1)

add_test(NAME test COMMAND test)
