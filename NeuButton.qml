import QtQuick
import Theming 1.0
import Qt5Compat.GraphicalEffects
import QtQuick.Controls

Item {
    id: root

    implicitWidth: 280
    implicitHeight: 40

    property alias buttonText : _textButtonText.text
    property color textColor: "black"

    signal clicked()

    state: "normal"

    Rectangle{
        id: _rectangleButtonBackgroud
        anchors.fill: parent
        radius: width/2
        color: Theme.baseColor

        Text{
            id: _textButtonText
            anchors.centerIn: parent
            font.pixelSize: 13
            color: textColor


        }
        BusyIndicator{
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 5
            width: 25
            height: 25
            visible: false
        }



    }

    DropShadow{
        id: _dropShadowTop
        source: _rectangleButtonBackgroud
        anchors.fill: _rectangleButtonBackgroud
        color: "white"
        horizontalOffset: -5
        verticalOffset: -5
        radius: 10
        transparentBorder: true
    }
    DropShadow{
        id: _dropShadowBottom
        source: _rectangleButtonBackgroud
        anchors.fill: _rectangleButtonBackgroud
        color: "#cccccc"
        horizontalOffset: 5
        verticalOffset: 5
        radius: 10
        transparentBorder: true
    }


    states:[
        State{
            name: "normal"

        },
        State{
            name: "hovered"
            PropertyChanges{
                target: _textButtonText
                color: Theme.primaryColor
                restoreEntryValues: true
            }
        }

    ]


    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onEntered: {
            root.state = "hovered"
        }
        onExited: {
            root.state = "normal"
        }

        onClicked: {
            root.clicked()
        }
    }

}
