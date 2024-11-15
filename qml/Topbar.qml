import QtQuick 2.12
import QtQuick.Window 2.2

Rectangle {
    id: root

    property alias text: text.text

    implicitHeight: 50
    implicitWidth: 200

    color: "black"
    opacity: 0.77

    Text {
        id: text
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pixelSize: 13

        text: "1Way Desktop"
        color: "white"
    }
}