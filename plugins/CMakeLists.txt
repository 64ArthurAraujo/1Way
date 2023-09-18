find_package(QmlPlugins)

macro(add_unity8_plugin PLUGIN VERSION PATH)
    export_qmlfiles(${PLUGIN} ${PATH} DESTINATION ${SHELL_INSTALL_QML} ${ARGN})
    export_qmlplugin(${PLUGIN} ${VERSION} ${PATH} DESTINATION ${SHELL_INSTALL_QML} ${ARGN})
endmacro()

add_subdirectory(Cursor)