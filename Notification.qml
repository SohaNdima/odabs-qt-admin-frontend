import QtQuick 2.0
import Qt5Compat.GraphicalEffects

Item {
    id: root

    width: 300
    height: 65

    state: "hidden"


    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        radius: 10
        color: "white"
        clip: true

        Text{
            id: _textNotificationMessage
            anchors.centerIn: parent
            anchors.margins: 10
            font.pixelSize: 11
            wrapMode: Text.WordWrap

        }
    }
    DropShadow{
        id: _dropShadow
        source: _rectangleBackground
        anchors.fill: _rectangleBackground
        radius: 10
        verticalOffset: 0
        horizontalOffset: 0
        transparentBorder: true
        color: "#cccccc"

    }

    states:[
        State{
            name: "success"
            PropertyChanges{
                target:_dropShadow
                color: "lime"
                visible: true
                opacity: 1
            }
        },
        State{
            name: "failure"
            PropertyChanges {
                target: _dropShadow
                color: "red"
                visible: true
                opacity: 1

            }
        },
        State{
            name: "information"
            PropertyChanges{
                target: _dropShadow
                color: "#cccccc"
                visible: true
                opacity: 1
            }
        },
        State{
            name: "hidden"
            PropertyChanges{
                target: root
                opacity: 0
                visible: false
            }
        }


    ]

    Timer{
        id: _timer
        interval: 4000
        onTriggered: root.state = "hidden"
    }

    onStateChanged: {
        _timer.start();
    }


    MouseArea{
        id: _mouseArea
        anchors.fill: parent
        onClicked: root.state = "hidden"

    }


    Connections{
        target: notificationManager

        function onShowNotification(status,message){
            _textNotificationMessage.text = message
            switch(status){
            case "Success": root.state = "success";break;
            case "Failure": root.state = "failure"; break;
            case "Information": root.state = "information";break;
            default: root.state="hidden";
            }
        }
    }

}
