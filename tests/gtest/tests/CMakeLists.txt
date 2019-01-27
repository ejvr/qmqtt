set(target_name qmqtt_tests)

# Find the required QT libraries
find_package(Qt5 REQUIRED COMPONENTS Core Network Test)

if (QMQTT_EXTERNAL_GTEST)
    find_package(GTest COMPONENTS gtest gmock REQUIRED CONFIG)
endif()

enable_testing()

set(CMAKE_AUTOMOC ON)

set(src
    clienttest.cpp
    customprinter.cpp
    frametest.cpp
    main.cpp
    messagetest.cpp
    networktest.cpp
    sockettest.cpp
    tcpserver.cpp)

set(headers
    customprinter.h
    iodevicemock.h
    networkmock.h
    socketmock.h
    tcpserver.h
    timermock.h)

add_executable(${target_name} ${src} ${headers})

target_compile_definitions(${target_name} PRIVATE -DQMQTT_LIBRARY_TESTS)

target_link_libraries(${target_name} PRIVATE 
    $<$<BOOL:${QMQTT_EXTERNAL_GTEST}>:GTest::>gtest
    $<$<BOOL:${QMQTT_EXTERNAL_GTEST}>:GTest::>gmock
    qmqtt_static
    Qt5::Test)

add_test(NAME ${target_name} COMMAND ${target_name})
