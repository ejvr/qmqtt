set(target_name example)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(${target_name} example.cpp example.hpp)

target_link_libraries(${target_name} qmqtt Qt5::Core)
