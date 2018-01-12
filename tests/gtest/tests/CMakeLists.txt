set(appname unittests)

# Find the required QT libraries
find_package(Qt5 COMPONENTS Core Network Test REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/mqtt")

file(GLOB unittest_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.cpp)
list(REMOVE_ITEM unittest_src routedmessagetests.cpp routertests.cpp routesubscriptiontests.cpp)

file(GLOB src RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${src_dir}/*.cpp"
    "${src_dir}/*.h")

add_executable(${appname} ${unittest_src} ${src})

if (BUILD_SHARED_LIBS)
    target_compile_definitions(${appname} PRIVATE -DGTEST_LINKED_AS_SHARED_LIBRARY=1)
endif (BUILD_SHARED_LIBS)

# This define force export of library symbols (dll_export)
target_compile_definitions(${appname} PRIVATE -DQMQTT_LIBRARY_TESTS -DQT_BUILD_MQTT_LIB)

target_include_directories(${appname} PRIVATE ${src_dir})
target_link_libraries(${appname} gtest gmock Qt5::Core Qt5::Network Qt5::Test)
