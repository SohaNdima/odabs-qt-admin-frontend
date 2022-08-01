import QtQuick
import QtQuick.Controls
import Theming 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    visibility: Qt.WindowFullScreen
    title: qsTr("ODABS Admin")
    background: Rectangle{
        color: Theme.baseColor
    }

    Loader{
        id: _loaderMain
        anchors.fill:parent
        source: authentication.authenticated ? "ContentViewManager.qml" : "LoginPage.qml"
    }

    DialogViewer{
        id: _dialogViewer
    }

    Notification{
        id: _notification
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

    }

}
