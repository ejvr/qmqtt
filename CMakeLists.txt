cmake_minimum_required(VERSION 2.8.11)

project(qmqtt_bundle)

enable_testing()

# Ensure the executables and dlls are copied to the same directory.
# Note that this may cause problems on windows when compiling for
# multiple platforms (eg. x86 and x64).
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)
add_test(run_tests unittests)
