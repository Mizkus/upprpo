enable_testing()


add_executable(test test.cpp)

target_link_libraries(test lib1 gtest gtest_main)

add_test(NAME test COMMAND test)
