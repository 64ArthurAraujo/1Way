file(GLOB QML_JS_FILES
    "*.qml"
    "*.js"
)
install(FILES ${QML_JS_FILES}
    DESTINATION build/qml
    )

set(QML_DIRS

    )

install(DIRECTORY ${QML_DIRS}
    DESTINATION build/qml
    )
