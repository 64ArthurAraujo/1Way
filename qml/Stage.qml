import QtQuick 2.12
import QtQuick.Window 2.2
import QtMir.Application 0.1

FocusScope {
    id: root
    anchors.fill: parent

    property QtObject applicationManager
    property QtObject topLevelSurfaceList
    property Item availableDesktopArea

    readonly property var mainApp: 0;

    Instantiator {
        model: root.applicationManager
        delegate: QtObject {
            property var stateBinding: Binding {
                target: model.application
                property: "requestedState"
                value: ApplicationInfoInterface.RequestedRunning
            }

            property var lifecycleBinding: Binding {
                target: model.application
                property: "exemptFromLifecycle"
                value: true
            }

            function onFocusRequested() {
                target: model.application

                onFocusRequested: {
                    // Application emits focusRequested when it has no surface (i.e. their processes died).
                    // Find the topmost window for this application and activate it, after which the app
                    // will be requested to be running.

                    for (var i = 0; i < appRepeater.count; i++) {
                        var appDelegate = appRepeater.itemAt(i);
                        if (appDelegate.application.appId === model.application.appId) {
                            appDelegate.activate();
                            return;
                        }
                    }

                    console.warn("Application requested te be focused but no window for it. What should we do?");
                }
            }
        }
    }

    FocusScope {
        id: appContainer
        objectName: "appContainer"
        anchors.fill: parent
        focus: true

        Repeater {
            id: appRepeater
            model: topLevelSurfaceList
            objectName: "appRepeater"

            function indexOf(delegateItem) {
                for (var i = 0; i < count; i++) {
                    if (itemAt(i) === delegateItem) {
                        return i;
                    }
                }
                return -1;
            }

            ApplicationWindow {
                anchors.fill: parent
                anchors.topMargin: 100
                surface: model.window.surface
            }
        }
    }
}