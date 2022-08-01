import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent
    visible: dialogManager.isOpen

    Rectangle{
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.7)

        MouseArea{
            anchors.fill: parent
            onClicked: dialogManager.closeDialog()
        }



        Loader{
            id: _dialogLoader
            anchors.centerIn: parent
            source: dialogManager.currentDialog
        }
    }


}
