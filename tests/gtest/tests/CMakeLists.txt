set(target_name unittests)

# Find the required QT libraries
find_package(Qt5 REQUIRED COMPONENTS Core Network Test)

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

target_link_libraries(${target_name} PRIVATE gtest gmock qmqtt_static Qt5::Test)

add_test(NAME run_tests COMMAND unittests)
