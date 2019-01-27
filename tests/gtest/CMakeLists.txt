option(QMQTT_EXTERNAL_GTEST "Use external google test libraries to compile unittests" OFF)

if (NOT QMQTT_EXTERNAL_GTEST)
    add_subdirectory(gtest)
endif()

add_subdirectory(tests)
