import QtQuick
import Qt5Compat.GraphicalEffects
import Theming 1.0


Item {
    id:root

    implicitHeight: 60
    implicitWidth: 300

    property bool centeredText : false
    property alias fieldName : _textPlaceholder.text
    property bool isPassword : false
    property alias inputValue : _textInput.text

    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        color: Theme.baseColor
        radius: 5

        Rectangle{
            id: _rectangleTextInputBackground
            anchors.fill: parent
            anchors.margins: 10
            color: "white"
            radius: 5

            Text{
                id: _textPlaceholder
                anchors.verticalCenter: _rectangleTextInputBackground.verticalCenter
                font.pixelSize: 15
                color: "#cccccc"
                anchors.left: parent.left
                anchors.leftMargin: 10
                visible: _textInput.text.length === 0 ? true: false

            }

            TextInput{
                id: _textInput
                anchors.fill: parent
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: centeredText ? Qt.AlignHCenter : Qt.AlignLeft
                font.pixelSize: 15
                color: "black"
                leftPadding: 10
                echoMode: isPassword ? TextInput.Password : TextInput.Normal


            }

        }


    }

    DropShadow{
        anchors.fill: _rectangleBackground
        source: _rectangleBackground
        color: _textInput.focus? Theme.primaryColor : "#cccccc"
        verticalOffset: 0
        horizontalOffset: 0
        radius: 10
        transparentBorder: true
    }









}
