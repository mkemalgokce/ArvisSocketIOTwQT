cmake_minimum_required(VERSION 3.14)

project(ArvisIOTServer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_library(WIRINGPI_LIBRARIES NAMES wiringPi REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebSockets)

add_executable(ArvisIOTServer
        main.cpp
        deviceconnector.cpp
        deviceconnector.h
        websocketserver.cpp
        websocketserver.h
        config.ini
)

target_link_libraries(ArvisIOTServer Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::WebSockets ${WIRINGPI_LIBRARIES})

install(TARGETS ArvisIOTServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})