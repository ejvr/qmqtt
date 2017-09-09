#!/bin/bash

BASE_DIR=$PWD

BUILD_DIR=.tmp/test/ssl
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX $BASE_DIR/qmqtt_test.pro && make CXX=$CXX && ./qmqtt_tests
if [[ $? -ne 0 ]] ; then
    exit 1
fi

cd  $BASE_DIR

BUILD_DIR=.tmp/test/no_ssl
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX DEFINES+=QT_NO_SSL $BASE_DIR/qmqtt_test.pro && make CXX=$CXX && ./qmqtt_tests
if [[ $? -ne 0 ]] ; then
    exit 1
fi

cd  $BASE_DIR

BUILD_DIR=.tmp/test/websockets
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX CONFIG+=QMQTT_WEBSOCKETS $BASE_DIR/qmqtt_test.pro && make CXX=$CXX && ./qmqtt_tests
if [[ $? -ne 0 ]] ; then
    exit 1
fi
