import QtQuick 2.15

Item {
    id: cursor
    width: 20
    height: 20

    Rectangle {
        width: parent.width
        height: 2
        color: "white"
        anchors.centerIn: parent
    }

    Rectangle {
        width: 2
        height: parent.height
        color: "white"
        anchors.centerIn: parent
    }
}