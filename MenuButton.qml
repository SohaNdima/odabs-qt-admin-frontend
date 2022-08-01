import QtQuick
import QtQuick.Layouts

Item {
    id: root
    implicitWidth: 220
    height: 35
    property alias menuLabel: _textMenuName.text
    property alias menuIcon: _imageIcon.source

    signal clicked()

    RowLayout{
        anchors.fill: parent

        Image{
            id: _imageIcon
            width: 15
            height: width
            sourceSize.width: width
            sourceSize.height: height
            Layout.alignment: Qt.AlignVCenter
            Layout.rightMargin: 20
        }
        Text{
            id: _textMenuName
            font.pixelSize: 11
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            horizontalAlignment: Qt.AlignLeft
        }
    }

    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
