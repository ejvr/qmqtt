TARGET = qmqtt
QT = core network

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    $$PWD/qmqtt_global.h \
    $$PWD/qmqtt.h \

include(mqtt.pri)

load(qt_module)
