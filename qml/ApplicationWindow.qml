import QtQuick 2.12

FocusScope {
    id: root

    property var surface: null

    onSurfaceChanged: {
        surfaceContainer.surface = surface;
    }

    Rectangle {
        id: background
        width: surfaceContainer.width
        height: 15
        anchors.left: surfaceContainer.left
        anchors.bottom: surfaceContainer.top
        radius: units.gu(.5)
        color: "#000000"
    }

    SurfaceContainer {
        id: surfaceContainer
        anchors.fill: parent
    }
}
