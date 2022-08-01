import QtQuick 2.0
import Theming 1.0
import Qt5Compat.GraphicalEffects

Item {
    id: root
    width: 25
    height: width

    state: "normal"

    property alias dayLabel: _textDay.text
    signal clicked()

   states:[
       State{
           name: "normal"
           PropertyChanges{
               target: _rectangleBackground
               color: Theme.baseColor
           }
           PropertyChanges{
               target: _textDay
               color: "black"
           }

       },
       State{
           name: "disabled"
           PropertyChanges{
               target: _rectangleBackground
               color: "#cccccc"
           }
           PropertyChanges{
               target: _textDay
               color: "gray"
           }
       },
       State{
           name: "booked"
           PropertyChanges{
               target: _rectangleBackground
               color: "lightsteelblue"
           }
           PropertyChanges{
               target: _textDay
               color: "black"
           }

       },
       State{
           name: "selected"
           PropertyChanges{
               target: _rectangleBackground
               color: Theme.primaryColor
           }
           PropertyChanges{
               target: _textDay
               color: "white"
           }
       }

   ]

    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        radius: width/2
        color: Theme.baseColor

        Text{
            id: _textDay
            anchors.centerIn: parent
            font.pixelSize: 10

        }

        Behavior on color{
            ColorAnimation{duration: 200}
        }
    }

    DropShadow{
        id: _dropShadow
        anchors.fill: _rectangleBackground
        source: _rectangleBackground
        color: "#cccccc"
        radius: 10
        transparentBorder: true
        verticalOffset: 0
        horizontalOffset: 0
    }


    MouseArea{
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        onClicked: {
            root.clicked()
            if(root.state !== "selected" && root.state !== "disabled" && root.state === "booked"){
                root.state = "selected"
            }
        }

    }





}
