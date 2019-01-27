#!/bin/bash

ctest --verbose --build-and-test . build-default --build-generator "Unix Makefiles" --test-command ctest -V
if [[ $? -ne 0 ]] ; then
    exit 1
fi

ctest --verbose --build-and-test . build-no-sll --build-generator "Unix Makefiles" --build-options -DQMQTT_SUPPORT_SSL=OFF --test-command ctest -V
if [[ $? -ne 0 ]] ; then
    exit 1
fi

ctest --verbose --build-and-test . build-websockets --build-generator "Unix Makefiles" --build-options -DQMQTT_SUPPORT_WEBSOCKETS=ON --test-command ctest -V
if [[ $? -ne 0 ]] ; then
    exit 1
fi

ctest --verbose --build-and-test . build-example --build-generator "Unix Makefiles" --build-options -DQMQTT_BUILD_EXAMPLE=ON --test-command ctest -V
if [[ $? -ne 0 ]] ; then
    exit 1
fi

ctest --verbose --build-and-test . build-no-test --build-generator "Unix Makefiles" --build-options -DBUILD_TESTING=OFF
if [[ $? -ne 0 ]] ; then
    exit 1
fi
