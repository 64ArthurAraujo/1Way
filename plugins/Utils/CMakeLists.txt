include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(
    SYSTEM
    ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
    ${DEVICEINFO_INCLUDE_DIRS}
    /usr/include/deviceinfo/
)

set(QMLPLUGIN_SRC
    activefocuslogger.cpp
    /usr/include/lomiri/shell/application/ApplicationManagerInterface.h
    /usr/include/lomiri/shell/application/ApplicationInfoInterface.h
    applicationsfiltermodel.cpp
    /usr/include/lomiri/shell/launcher/AppDrawerModelInterface.h
    /usr/include/lomiri/shell/launcher/LauncherItemInterface.h
    /usr/include/lomiri/shell/launcher/LauncherModelInterface.h
    appdrawerproxymodel.cpp
    constants.cpp
    WindowInputMonitor.cpp
    inputwatcher.cpp
    qlimitproxymodelqml.cpp
    lomirisortfilterproxymodelqml.cpp
    Timer.cpp
    lomirimenumodelpaths.cpp
    windowinputfilter.cpp
    easingcurve.cpp
    windowstatestorage.cpp
    timezoneFormatter.cpp
    inputeventgenerator.cpp
    deviceconfig.cpp
    globalfunctions.cpp
    URLDispatcher.cpp
    tabfocusfence.cpp
    expressionfiltermodel.cpp
    quicklistproxymodel.cpp
    plugin.cpp
    )

add_library(Utils-qml SHARED
    ${QMLPLUGIN_SRC}
    )

target_link_libraries(Utils-qml
    Qt5::Qml Qt5::Quick Qt5::DBus Qt5::Network Qt5::Gui Qt5::Sql Qt5::Concurrent
    ${DEVICEINFO_LDFLAGS}
)

# Because this is an internal support library, we want
# to expose all symbols in it. Consider changing this
# either to a static library or just using the
# files directly in targets.
set_target_properties(Utils-qml PROPERTIES COMPILE_FLAGS -fvisibility=default)

add_unity8_plugin(Utils 0.1 Utils TARGETS Utils-qml)
