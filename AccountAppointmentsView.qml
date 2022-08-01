import QtQuick 2.0
import QtQuick.Layouts

Item {
    id: root
    width: parent.width

    property alias appointmentsModel: _listViewAppointments.model

    ColumnLayout{
        anchors.fill: parent

        Text{
            id: _textHeading
            text: "Appointments Schedule"
            color: "black"
            font.pixelSize: 15
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.leftMargin: 10
            Layout.topMargin: 25
            Layout.bottomMargin: 30

        }

        RowLayout{
            id: _layout1
            width: root.width
            height: 60
            Layout.maximumHeight: 60
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            Rectangle{
                id: _rectangleBelow30Mins
                Layout.fillHeight: true
                Layout.minimumWidth: (20/100) * _layout1.width
                width: (20/100) * _layout1.width
                color: Qt.lighter("green")

                Text{
                    text: "Below 30 minutes"
                    font.pixelSize: 12
                    anchors.centerIn: parent
                    color:"white"
                }
            }
            Rectangle{
                id: _rectangleBetween30To60Mins
                Layout.fillHeight: true
               Layout.fillWidth: true
                color: Qt.lighter("orange")
                Text{
                    text: "Between 30 minutes to 1 hour"
                    font.pixelSize: 12
                    anchors.centerIn: parent
                    color:"white"
                }

            }
            Rectangle{
                id: _rectangleAbove60Mins
                Layout.fillHeight: true
                Layout.minimumWidth: (30/100) * _layout1.width
                width: (30/100) * _layout1.width
                color: Qt.lighter("red")
                Text{
                    text: "Above 1 hour"
                    font.pixelSize: 12
                    anchors.centerIn: parent
                    color:"white"
                }
            }
        }


        ListView{
            id: _listViewAppointments
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 15
            clip: true
            spacing: 20
            delegate: AppointmentsDelegate{
                width: ListView.view.width
                startTime: model.Time
                endTime: model.EndTime
                patientName: model.Patient
                appointmentType: model.AppointmentType
                appointmentStatus: model.AppointmentStatus
            }


        }
    }



}
