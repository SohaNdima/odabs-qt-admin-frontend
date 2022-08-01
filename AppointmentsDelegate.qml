import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls.Imagine
import Theming 1.0

Item {
    id: root

    width: parent.width
    height: 80

    property alias startTime : _textStartTime.text
    property alias endTime: _textEndTime.text
    property alias patientName: _textPatientName.text
    property alias appointmentType: _textAppointmentType.text
    property alias appointmentStatus: _textAppointmentStatus.text

    Rectangle{
        anchors.fill: parent
        color: "transparent"

        RowLayout{
            anchors.fill: parent

            RowLayout{
                id: _layoutLeft
                Layout.fillHeight: true
                Layout.minimumWidth: 180



                ColumnLayout{
                    id: _layoutCol1
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignRight

                    Text{
                        id: _textStartTime
                        font.pixelSize: 10
                        color: "black"
                        Layout.alignment: Qt.AlignRight

                    }
                    Item{Layout.fillHeight: true}
                    Text{
                        id: _textEndTime
                        font.pixelSize: 10
                        color: "black"
                        Layout.alignment: Qt.AlignRight
                    }
                }
                ColumnLayout{
                    id: _layoutCol2
                    Layout.fillHeight: true
                    Rectangle{
                        width: 10
                        height: width
                        radius: width/2
                        color: "transparent"
                        border.width: 1
                        border.color: "black"
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Rectangle{
                        width: 1
                        Layout.fillHeight: true
                        color: "black"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Rectangle{
                        width: 10
                        height: width
                        radius: width/2
                        color: "transparent"
                        border.width: 1
                        border.color: "black"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
            Rectangle{
                id: _rectangleBackground1
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: Qt.rgba(1,1,0,0.3)

                Rectangle{
                    id: _rectangleTimeFrameIndicator
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.margins: 5
                    radius: 5
                    width: {
                        if(model.Duration <= 30){
                            return 0.3 * parent.width
                        }
                        if(model.Duration > 30 && model.Duration <= 60){
                            return 0.4 * parent.width
                        }
                        if(model.Duration > 60){
                            return 0.7* parent.width
                        }
                    }

                    color: {
                        if(model.Duration <= 30){
                            return Qt.rgba(0,1,0,0.5)
                        }
                        if(model.Duration > 30 && model.Duration <= 60){
                            return Qt.rgba(1,1,0,0.5)
                        }
                        if(model.Duration > 60){
                            return Qt.rgba(1,0,0,0.5)
                        }
                    }


                    ColumnLayout{
                        id: _layoutAppointmentDetails
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        anchors.right: parent.right
                        anchors.margins: 5

                        Text{
                            id: _textPatientName
                            font.pixelSize: 12
                            color: "black"
                            font.bold: true
                        }
                        Text{
                            id: _textAppointmentType
                            font.pixelSize: 11
                            color: "black"
                        }

                        Item{Layout.fillHeight: true}

                        Text{
                            id: _textAppointmentStatus
                            font.pixelSize: 10
                            color: "white"

                        }

                    }
                }

                Rectangle{
                    id: _rectangleCancelAppointment
                    width: 30
                    height: width
                    radius: width/2
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 10
                    color: Qt.rgba(1,1,1,0.3)

                    Image{
                        id: _imageDeleteIcon
                        width: 15
                        height: 15
                        sourceSize.width: 15
                        sourceSize.height: 15
                        anchors.centerIn: parent
                        source: "qrc:/assets/icons/delete.svg"

                    }

                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
        }
    }

}
