cmake_minimum_required(VERSION 2.8.11)

project(qmqtt)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)
add_test(run_tests unittests)
