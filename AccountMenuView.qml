import QtQuick
import QtQuick.Layouts
import Theming 1.0
import Qt5Compat.GraphicalEffects

Item {
    id: root
    width: 270

    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        color: Qt.rgba(0,0,0,0.03)


        ColumnLayout{
            id: _layoutMain
            anchors.fill: parent
            anchors.margins: 10


            Item{
                id: _itemUserIconWrapper
                width: 70
                height: 70
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.topMargin: 20
                Rectangle{
                    id: _rectangleUserIconWrapper
                    width: 70
                    height: 70
                    radius: width/2
                    color: Theme.baseColor

                    Image{
                        id: _imageAccountImage
                        anchors.fill: parent
                        source: "qrc:/assets/images/account_image.png"
                        layer.enabled: true
                        layer.effect: OpacityMask{
                            maskSource: Item{
                                width: _imageAccountImage.width
                                height: width
                                Rectangle{
                                    anchors.centerIn: parent
                                    width: parent.width
                                    height: parent.width
                                    radius: width/2
                                }
                            }
                        }
                    }


                }
                DropShadow{
                    anchors.fill: _rectangleUserIconWrapper
                    source: _rectangleUserIconWrapper
                    verticalOffset: 0
                    horizontalOffset: 0
                    transparentBorder: true
                    color: "#cccccc"
                    radius: 10
                }
            }


            Text{
                id: _textUsername
                font.pixelSize: 11
                color: "black"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                text: authentication.name

            }

            Rectangle{
                Layout.fillWidth: true
                height: 1
                color: "#cccccc"
                Layout.topMargin: 10
            }

            MenuButton{
                id: _menuButtonAppointments
                menuLabel: "Appointments"
                menuIcon: "qrc:/assets/icons/book-appointments.svg"
                Layout.topMargin: 25
            }
            MenuButton{
                id: _menuButtonDoctors
                menuLabel: "Doctors"
                menuIcon: "qrc:/assets/icons/doctor.svg"
                onClicked: dialogManager.openDialog("NewDoctorDialog.qml")
            }
            MenuButton{
                id: _menuButtonSettings
                menuLabel: "Settings"
                menuIcon: "qrc:/assets/icons/settings.svg"
            }


            Item{
                Layout.fillHeight: true
            }

            NeuButton{
                id: _buttonLogout
                Layout.fillWidth: true
                buttonText: "Logout"
                onClicked: {
                    authentication.logout()
                }


            }
        }
    }



}
