cmake_minimum_required(VERSION 3.11)

project(tcp-server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/widget/tcpserverwidget.cpp
    src/widget/model/clientstablemodel.cpp
    src/widget/entity/client.cpp
)

set(HEADERS
    src/mainwindow.h
    src/widget/tcpserverwidget.h
    src/widget/model/clientstablemodel.h
    src/widget/entity/client.h
)

set(FORMS
    src/mainwindow.ui
    src/widget/tcpserverwidget.ui
)

add_executable(tcp-server
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_link_libraries(tcp-server PRIVATE Qt5::Widgets Qt5::Network)
