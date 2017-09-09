#!/bin/bash

BASE_DIR=$PWD

BUILD_DIR=.tmp/build/ssl
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX $BASE_DIR/qmqtt.pro && make CXX=$CXX
if [[ $? -ne 0 ]] ; then
    exit 1
fi

cd  $BASE_DIR

BUILD_DIR=.tmp/build/no_sll
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX DEFINES+=QT_NO_SSL $BASE_DIR/qmqtt.pro && make CXX=$CXX
if [[ $? -ne 0 ]] ; then
    exit 1
fi

cd  $BASE_DIR

BUILD_DIR=.tmp/build/websocket
mkdir -p $BUILD_DIR
cd $BUILD_DIR
qmake CXX=$CXX CONFIG+=QMQTT_WEBSOCKETS $BASE_DIR/qmqtt.pro && make CXX=$CXX
if [[ $? -ne 0 ]] ; then
    exit 1
fi
