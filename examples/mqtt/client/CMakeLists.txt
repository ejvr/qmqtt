cmake_minimum_required(VERSION 2.8.11)

project(example)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} example.cpp)
target_link_libraries(${PROJECT_NAME} qmqtt)
