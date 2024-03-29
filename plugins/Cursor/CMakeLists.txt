add_subdirectory(3rd_party)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/xcursor
)

include_directories(
    SYSTEM
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
)

set(QMLPLUGIN_SRC
    plugin.cpp
    CursorImageInfo.cpp
    CursorImageProvider.cpp
    MousePointer.cpp
    InputDispatcherFilter.cpp
    # We need to run moc on this header
    /usr/include/lomiri/shell/application/MirMousePointerInterface.h
    )

add_library(Cursor-qml SHARED
    ${QMLPLUGIN_SRC}
    )

target_link_libraries(Cursor-qml
    xcursorloader-static
    ${QT5PLATFORM_SUPPORT_LDFLAGS}
    Qt5::Qml Qt5::Quick Qt5::Svg
)

add_unity8_plugin(Cursor 1.1 Cursor TARGETS Cursor-qml)
