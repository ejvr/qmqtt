cmake_minimum_required(VERSION 2.8.11)

project(example)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Find all source files part of the library
file(GLOB_RECURSE src *.cpp)
# Find the headers, used to generate the moc files
file(GLOB_RECURSE headers *.hpp)

add_executable(${PROJECT_NAME} ${src} ${headers})
target_link_libraries(${PROJECT_NAME} qmqtt)
