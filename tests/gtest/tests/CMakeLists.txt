cmake_minimum_required(VERSION 2.8.11)

project(unittests)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core Network Test REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/mqtt")

include_directories(${src_dir})

file(GLOB unittest_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.cpp)
list(REMOVE_ITEM unittest_src routedmessagetests.cpp routertests.cpp routesubscriptiontests.cpp)

file(GLOB src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${src_dir}/*.cpp"
    "${src_dir}/*.h")

# This define force export of library symbols (dll_export)
add_definitions(-DQMQTT_LIBRARY_TESTS -DQT_BUILD_MQTT_LIB)

add_executable(${PROJECT_NAME} ${unittest_src} ${src})
target_link_libraries(${PROJECT_NAME} gtest gmock Qt5::Core Qt5::Network Qt5::Test)
