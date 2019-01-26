cmake_minimum_required(VERSION 3.5)

project(qmqtt VERSION 0.1 LANGUAGES CXX)

include(CPack)
include(CTest)

option(QMQTT_BUILD_EXAMPLE "Build example" OFF)

add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
if (QMQTT_BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()

install(EXPORT ${CMAKE_PROJECT_NAME}
    NAMESPACE ${CMAKE_PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
    FILE ${CMAKE_PROJECT_NAME}Config.cmake)
