import QtMir.Application 0.1 // for MirSurfaceItem
import Utils 0.1 // for InputWatcher
import QtQuick 2.12

FocusScope {
    id: root
    objectName: "surfaceContainer"

    // Must be set from outside
    property var surface: null

    // Might be changed from outside
    property int requestedWidth: -1
    property int requestedHeight: -1
    property bool interactive
    property int surfaceOrientationAngle: 0
    property bool isPromptSurface: false
    // FIME - dont export, use interactive property. Need to fix qtmir to handle consumesInputChanged
    // to update surface activeFocus. See mock MirSurfaceItem.
    property alias consumesInput: surfaceItem.consumesInput

    property bool hadSurface: false

    onSurfaceChanged: {
        // Not a binding because animations might remove the surface from the surfaceItem
        // programatically (in order to signal that a zombie surface is free for deletion),
        // even though root.surface is still !null.
        console.log("SurfaceContainer: Surface changed to: " + surface)

        if (surface != null)
            root.hadSurface = true;

        surfaceItem.surface = surface;
    }

    InputWatcher {
        target: surfaceItem
        onTargetPressedChanged: {
            if (targetPressed && root.interactive) {
                root.focus = true;
                root.forceActiveFocus();
            }
        }
    }

    MirSurfaceItem {
        id: surfaceItem
        objectName: "surfaceItem"
        anchors.fill: parent

        focus: true

        fillMode: MirSurfaceItem.PadOrCrop
        consumesInput: true

        surfaceWidth: root.requestedWidth
        surfaceHeight: root.requestedHeight

        enabled: true
        antialiasing: false
        orientationAngle: root.surfaceOrientationAngle
    }
}