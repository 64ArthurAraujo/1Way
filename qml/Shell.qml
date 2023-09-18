import QtQuick 2.12
import QtQuick.Window 2.2
import QtMir.Application 0.1
import Cursor 1.1

Item {
    id: root

    Wallpaper {
        id: wallpaper
        z: -2
        anchors.fill: parent
    }

    Topbar {
        id: topbar
        height: 22.5
        width: root.width
        anchors { right: parent.right; top: parent.top }
    }

    Cursor {
        id: cursor
        objectName: "cursor"
        opacity: 1

        z: 10
        topBoundaryOffset: 0
        enabled: true
        visible: enabled

        property bool mouseNeverMoved: true
        Binding {
            target: cursor; property: "x"; value: shell.width / 2
            when: cursor.mouseNeverMoved && cursor.visible
        }
        Binding {
            target: cursor; property: "y"; value: shell.height / 2
            when: cursor.mouseNeverMoved && cursor.visible
        }

        height: units.gu(3)
    }

    // button to quit so we dont have to stop the program process everytime we make a change to qml
    Button {
        anchors { right: parent.right; bottom: parent.bottom }
        height: 30
        width: 80
        text: "Quit 1Way"
        onClicked: Qt.quit()
    }

}
