cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0022 NEW)

project(1way)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -Wall -pedantic -Wextra -fPIC -Wnon-virtual-dtor -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,defs")
set(CMAKE_AUTOMOC ON)
set(SHELL_APP_DIR ${CMAKE_INSTALL_DATADIR}/1way)

include(FindPkgConfig)
pkg_check_modules(MIRAL miral REQUIRED)
find_package(Qt5Core 5.6 REQUIRED)
find_package(Qt5Qml 5.6 REQUIRED)
find_package(Qt5Quick 5.6 REQUIRED)
find_package(Qt5Gui 5.6 REQUIRED)
find_package(Qt5DBus 5.6 REQUIRED)
find_package(Qt5Concurrent 5.6 REQUIRED)
find_package(Qt5Sql 5.6 REQUIRED)
find_package(Qt5Test 5.6 REQUIRED)
find_package(Qt5Svg 5.6 REQUIRED)
find_package(Qt5Network 5.6 REQUIRED)
find_package(Qt5Xml 5.6 REQUIRED)


add_subdirectory(qml)

file(GLOB ONEWAY_SRC
    "src/*.h"
    "src/*.cc"
)

add_executable(1way ${ONEWAY_SRC} ${QML_SRC})

target_include_directories(1way PUBLIC SYSTEM ${MIRAL_INCLUDE_DIRS})
target_include_directories(1way PRIVATE
    /usr/include/qt5/QtCore
    /usr/include/qt5
    /usr/include/qt5/QtGui
    /usr/include/qt5/QtQml
    /usr/include/qt5/QtQuick
    /usr/include/qt5/QtQuick/5.15.10
    /usr/include/qt5/QtQuick/5.15.10/QtQuick
    /usr/include/qt5/QtQml/5.15.10
    /usr/include/qt5/QtQml/5.15.10/QtQml
    /usr/include/qt5/QtCore/5.15.10/QtCore/private
    /usr/include/qt5/QtCore/5.15.10/QtCore
    /usr/include/qt5/QtCore/5.15.10
    /usr/include/qt5/QtGui/5.15.10/QtGui
    /usr/include/qt5/QtGui/5.15.10
)

target_link_libraries(1way 
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::Gui
    Qt5::DBus
    Qt5::Concurrent
    Qt5::Sql
    Qt5::Test
    Qt5::Svg
    Qt5::Network
    Qt5::Xml
    ${MIRAL_LDFLAGS}
)

install(PROGRAMS ${CMAKE_BINARY_DIR}/1way
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

install(FILES ${CMAKE_SOURCE_DIR}/1way.desktop
    DESTINATION /usr/share/wayland-sessions/
)

install(FILES ${CMAKE_SOURCE_DIR}/1way.desktop
    DESTINATION /usr/share/applications/
)
