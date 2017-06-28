TARGET = qmqtt_tests
QT = core network testlib

DEFINES += QMQTT_LIBRARY_TESTS

include(src/mqtt/mqtt.pri)
include(tests/gtest/gtest/gtest.pri)

SOURCES += \
    tests/gtest/tests/clienttest.cpp \
    tests/gtest/tests/tcpserver.cpp \
    tests/gtest/tests/main.cpp \
    tests/gtest/tests/customprinter.cpp \
    tests/gtest/tests/networktest.cpp \
    tests/gtest/tests/messagetest.cpp \
    tests/gtest/tests/frametest.cpp \
    tests/gtest/tests/sockettest.cpp

HEADERS += \
    $$PUBLIC_HEADERS \
    $$PRIVATE_HEADERS \
    tests/gtest/tests/tcpserver.h \
    tests/gtest/tests/customprinter.h \
    tests/gtest/tests/networkmock.h \
    tests/gtest/tests/socketmock.h \
    tests/gtest/tests/timermock.h \
    tests/gtest/tests/iodevicemock.h
