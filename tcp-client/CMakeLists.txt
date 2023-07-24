cmake_minimum_required(VERSION 3.5)

project(tcp-client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Network REQUIRED)

set(SOURCES
        src/main.cpp
        src/mainwindow.cpp
)

set(HEADERS
        src/mainwindow.h
)

set(FORMS
        src/mainwindow.ui
)

add_executable(tcp-client
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)


target_link_libraries(tcp-client PRIVATE Qt5::Widgets Qt5::Network)
