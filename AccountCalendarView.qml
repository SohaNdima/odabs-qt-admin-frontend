import QtQuick 2.0
import QtQuick.Controls.Imagine
import QtQuick.Layouts

Item {
    id: root
    width: 350

    property date today: new Date()
    property string selectedDayOfWeek: evaluateDayOfWeek(today.getUTCDay())
    property string selectedDay: today.getDate()
    property string selectedMonth: evaluateMonth(today.getMonth())

    signal dateHasAppointments(var date)
    signal datePicked(var date)

    function evaluateDayOfWeek(value){
        switch(value){
        case 0: return "Sunday"
        case 1: return "Monday"
        case 2: return "Tuesday"
        case 3: return "Wednesday"
        case 4: return "Thursday"
        case 5: return "Friday"
        case 6: return "Sartuday"
        }
    }

    function evaluateMonth(value){
        switch(value){
        case 0: return "January"
        case 1: return "February"
        case 2: return "March"
        case 3: return "April"
        case 4: return "May"
        case 5: return "June"
        case 6: return "July"
        case 7: return "August"
        case 8: return "September"
        case 9: return "October"
        case 10: return "November"
        case 11: return "December"

        }
    }

    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.07)


        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10

            Text {
                id: _textSelectedDate
                text: "<font> <strong>"+selectedDayOfWeek+"</strong> - "+ selectedDay+" "+ selectedMonth +"</font>"
                textFormat: Text.RichText
                font.pixelSize: 13
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                Layout.topMargin: 30
            }

            ListView{
                id: _listViewCalendarContainer
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.topMargin: 20
                spacing: 20
                clip: true
                model: CalendarModel{
                    from: new Date()
                    to: new Date(today.setDate(today.getDate() + 30))
                }
                delegate: ColumnLayout{
                    width:_listViewCalendarContainer.width
                    spacing: 10



                    Rectangle{
                        id: _rectangleMonthHeading
                        width: _textMonthHeading.width + 20
                        height: 30
                        radius: width/2
                        color: Qt.lighter("orange")
                        Layout.alignment: Qt.AlignLeft
                        Layout.bottomMargin: 5
                        Layout.leftMargin: 10
                        Text{
                            id: _textMonthHeading
                            text: _monthGrid.title
                            font.pixelSize: 10
                            anchors.centerIn: parent

                        }
                    }

                    DayOfWeekRow{
                        id: _dayOfWeekRow
                        Layout.fillWidth: true
                        locale: _monthGrid.locale
                        delegate: Text{
                            width: 30
                            height: 30
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                            text: shortName
                            font.pixelSize: 10
                        }

                    }
                    MonthGrid{
                        id: _monthGrid

                        signal dateSelected(var date)

                        locale: Qt.locale("en_US")
                        month: model.month
                        year: model.year
                        Layout.fillWidth: true
                        delegate: MonthDateDelegate{
                            id: _monthDateDelegate
                            dayLabel: model.day
                            state: evaluateState()
                            onClicked: {
                                _monthGrid.dateSelected(model.date)
                                root.datePicked(model.date)
                            }

                            Connections{
                                target: _monthGrid
                                ignoreUnknownSignals: true

                                function onDateSelected(date){

                                    if(model.date !== date && _monthDateDelegate.state === "selected" && _monthDateDelegate.state !== "disabled"){
                                        _monthDateDelegate.state = "normal"
                                    }
                                }
                            }

                            Connections{
                                target: root
                                ignoreUnknownSignals: true

                                function onDateHasAppointments(date){

                                    if(compareDates(model.date,date) && _monthDateDelegate.state !== "disabled"){

                                        _monthDateDelegate.state = "booked"
                                    }
                                }
                            }

                            function evaluateState(){
                                if(model.month !== _monthGrid.month || model.date < new Date()){
                                    return "disabled"
                                }
                                return "normal"
                            }
                        }


                    }
                }
            }
        }


    }



    function compareDates(date1,date2){

        return date1.getDate() === date2.getDate() && date1.getMonth() === date2.getMonth() && date1.getYear() === date2.getYear()
    }




}
