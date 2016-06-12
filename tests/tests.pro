QT += network testlib
QT -= gui

TARGET = qmqtt_tests

DEFINES += QMQTT_LIBRARY_TESTS

include(../src/qmqtt.pri)
include(../gtest/gtest.pri)

SOURCES += \
    clienttest.cpp \
    tcpserver.cpp \
    main.cpp \
    customprinter.cpp \
    networktest.cpp \
    messagetest.cpp \
    frametest.cpp \
    sockettest.cpp

HEADERS += \
    tcpserver.h \
    customprinter.h \
    networkmock.h \
    socketmock.h \
    timermock.h \
    iodevicemock.h
