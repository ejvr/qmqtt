find_package(Qt5 COMPONENTS Core Network REQUIRED)

set(qmqtt_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/qmqtt/include/qmqtt)
set(qmqtt_BIN_DIR ${CMAKE_CURRENT_LIST_DIR}/qmqtt/bin)
set(qmqtt_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/qmqtt/lib)
set(qmqtt_LIB_DEPENDENCIES "Qt5::Network")

add_library(qmqtt SHARED IMPORTED)

target_include_directories(qmqtt INTERFACE ${qmqtt_INCLUDE_DIR})

set_target_properties(qmqtt PROPERTIES
    "INTERFACE_LINK_LIBRARIES" "${qmqtt_LIB_DEPENDENCIES}"
    "IMPORTED_LOCATION_RELEASE" ${qmqtt_BIN_DIR}/qmqtt.dll
    "IMPORTED_IMPLIB_RELEASE" ${qmqtt_LIB_DIR}/qmqtt.lib
    "IMPORTED_LOCATION_DEBUG" ${qmqtt_BIN_DIR}/qmqttd.dll
    "IMPORTED_IMPLIB_DEBUG" ${qmqtt_LIB_DIR}/qmqttd.lib)
