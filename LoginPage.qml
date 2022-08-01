import QtQuick
import QtQuick.Layouts



Item {
    id: root

   ColumnLayout{
       id: _layoutMain
       anchors.centerIn: parent
       spacing: 10

       Text{
           id: _textTitle
           text: "ODABS"
           textFormat: Text.RichText
           font.pixelSize: 30
           Layout.alignment: Qt.AlignHCenter
           Layout.bottomMargin: 30
       }

       NeuTextField{
           id: _textFieldUsername
           Layout.alignment: Qt.AlignHCenter
           width: 300
           height: 60
           fieldName: "Username"
       }
       NeuTextField{
           id: _textFieldPassword
           Layout.alignment: Qt.AlignHCenter
           width: 300
           height: 60
           fieldName: "Password"
           isPassword: true
       }

       NeuButton{
           id: _buttonLogin
           buttonText: "LOGIN"
           Layout.alignment: Qt.AlignHCenter
           Layout.topMargin: 25
           onClicked: {
                authentication.login(_textFieldUsername.inputValue,_textFieldPassword.inputValue)

           }
       }


   }

}
