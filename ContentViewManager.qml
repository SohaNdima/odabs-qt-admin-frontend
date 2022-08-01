import QtQuick 2.0
import QtQuick.Layouts
import CustomModels 1.0

Item {
    id: root
    anchors.fill: parent


    RowLayout{
        id: _layoutMain
        anchors.fill: parent

        AccountMenuView{
            id: _accountMenuView
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft
        }

        AccountAppointmentsView{
            id: _accountAppointmentsView
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        AccountCalendarView{
            id: _accountCalendarView
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignRight
            Layout.minimumWidth: 350
            Layout.maximumWidth: 350

            Connections{
                target: _appointmentDateListModel
                ignoreUnknownSignals: true

                function onDateHasAppointments(date){

                    _accountCalendarView.dateHasAppointments(date)
                }
            }
        }
    }


    AppointmentDateListModel{
        id: _appointmentDateListModel

    }

    Connections{
        target: _accountCalendarView
        ignoreUnknownSignals: true

        function onDatePicked(date){
            _accountAppointmentsView.appointmentsModel = _appointmentDateListModel.extractAppointmentDetailsListModelByDate(date)
        }
    }


    Component.onCompleted: {
        _appointmentDateListModel.fetchAppointments("All","");
    }

}
