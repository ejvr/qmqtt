set(libname qmqtt)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(CMAKE_AUTOMOC ON)

# Find all source files part of the library
file(GLOB_RECURSE src *.cpp)
# Find the headers, used to generate the moc files
file(GLOB_RECURSE headers *.h)

# This define force export of library symbols (dll_export)
add_definitions(-DQT_BUILD_MQTT_LIB)

add_library(${libname} SHARED ${src} ${headers})
target_include_directories(${libname} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${libname} PUBLIC Qt5::Core Qt5::Network)
