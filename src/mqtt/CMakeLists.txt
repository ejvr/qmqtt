set(target_name qmqtt)

# Find the required QT libraries
find_package(Qt5 REQUIRED COMPONENTS Core Network)

if (QMQTT_SUPPORT_WEBSOCKETS)
    find_package(Qt5 REQUIRED COMPONENTS WebSockets)
endif()

set(CMAKE_AUTOMOC ON)

set(public_headers 
    qmqtt.h 
    qmqtt_message.h
    qmqtt_client.h
    qmqtt_global.h
    qmqtt_networkinterface.h
    qmqtt_routedmessage.h
    qmqtt_routesubscription.h
    qmqtt_socketinterface.h
    qmqtt_timerinterface.h)

set (private_headers
    qmqtt_client_p.h
    qmqtt_message_p.h
    qmqtt_network_p.h
    qmqtt_socket_p.h
    qmqtt_timer_p.h)

set (src
    qmqtt_client.cpp
    qmqtt_client_p.cpp
    qmqtt_frame.cpp
    qmqtt_message.cpp
    qmqtt_network.cpp
    qmqtt_router.cpp
    qmqtt_routesubscription.cpp
    qmqtt_socket.cpp
    qmqtt_timer.cpp)

if (QMQTT_SUPPORT_WEBSOCKETS)
    list(APPEND private_headers qmqtt_websocketiodevice_p.h qmqtt_websocket_p.h)
    list(APPEND src qmqtt_websocket.cpp qmqtt_websocketiodevice.cpp)
endif()

if (QMQTT_SUPPORT_SSL)
    list(APPEND private_headers qmqtt_ssl_socket_p.h)
    list(APPEND src qmqtt_ssl_socket.cpp)
endif()

add_library(${target_name} SHARED ${src} ${public_headers} ${private_headers})

# This define forces export of library symbols (dll_export)
target_compile_definitions(${target_name} PRIVATE -DQT_BUILD_QMQTT_LIB)
target_include_directories(${target_name} PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(${target_name} PUBLIC Qt5::Core Qt5::Network)

if (QMQTT_SUPPORT_WEBSOCKETS)
    target_compile_definitions(${target_name} PUBLIC -DQT_WEBSOCKETS_LIB)
    target_link_libraries(${target_name} PUBLIC Qt5::WebSockets)
endif()

if (!QMQTT_SUPPORT_SSL)
    target_compile_definitions(${target_name} PUBLIC -DQT_NO_SSL)
endif()

set_target_properties(${target_name} PROPERTIES
    FRAMEWORK TRUE
    PUBLIC_HEADER "${public_headers}")

install(TARGETS ${target_name}
    EXPORT qmqtt
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (QMQTT_BUILD_TESTS)
    set(static_target_name ${target_name}_static)

    add_library(${static_target_name} STATIC ${src} ${public_headers} ${private_headers})

    target_compile_definitions(${static_target_name} PUBLIC -DQT_BUILD_QMQTT_LIB)
    target_include_directories(${static_target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${static_target_name} PUBLIC Qt5::Core Qt5::Network)

    if (QMQTT_SUPPORT_WEBSOCKETS)
        target_compile_definitions(${static_target_name} PUBLIC -DQT_WEBSOCKETS_LIB)
        target_link_libraries(${static_target_name} PUBLIC Qt5::WebSockets)
    endif()

    if (!QMQTT_SUPPORT_SSL)
        target_compile_definitions(${static_target_name} PUBLIC -DQT_NO_SSL)
    endif()
endif()
