import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Image {
        id: image1
        x: 10
        y: 10
        anchors.fill: parent
        source: "/home/arthur/Downloads/mm.jpg"
    }

    Cursor {
        id: customCursor
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onPositionChanged: {
            customCursor.x = mouse.x - customCursor.width / 2;
            customCursor.y = mouse.y - customCursor.height / 2;
        }
    }
}
