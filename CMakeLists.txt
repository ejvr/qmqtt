cmake_minimum_required(VERSION 3.5)

project(qmqtt VERSION 0.1 LANGUAGES CXX)

include(CPack)
include(CTest)
include(GNUInstallDirs)

option(QMQTT_SUPPORT_SSL "Add support for SSL sockets" ON)
option(QMQTT_SUPPORT_WEBSOCKETS "Add support for websockets" OFF)
option(QMQTT_BUILD_TESTS "Build unit tests" OFF)
option(QMQTT_BUILD_EXAMPLE "Build example" OFF)

add_subdirectory(src)
if (QMQTT_BUILD_TESTS)
    add_subdirectory(tests)
endif()
if (QMQTT_BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()

install(EXPORT ${CMAKE_PROJECT_NAME}
    NAMESPACE ${CMAKE_PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
    FILE ${CMAKE_PROJECT_NAME}Config.cmake)
