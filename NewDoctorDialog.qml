import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls.Imagine
import CustomModels

Item {
    id: root

    width: 520
    height: 500

    QtObject{
        id: _newDoc
        property string fullname
        property string username
        property string password
        property variant specializationFields : []

        function removeField(id){
            for(let i =0; i < specializationFields.length; i++){
                if(id === specializationFields[i]){
                    specializationFields.splice(i,1);
                }
            }
        }
        function addField(id){
            let exists = false
            for(let i =0; i < specializationFields.length; i++){
                if(id === specializationFields[i]){
                    exists = true
                    break
                }
            }

            if(!exists){
                specializationFields.push(id)
            }

        }
    }

    Rectangle{
        id: _rectangleBackground
        anchors.fill: parent
        color: "white"
        radius: 10

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10

            Text{
                id: _textTitle
                text: "Add New Doctor"
                font.pixelSize: 20
                Layout.alignment: Qt.AlignHCenter
                Layout.bottomMargin: 20
            }

            TextField{
                id: _textFieldName
                placeholderText: "Doctor's Fullname"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                onEditingFinished: {
                    _newDoc.fullname = _textFieldName.text
                }
            }
            TextField{
                id: _textFieldUsername
                placeholderText: "Username"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                onEditingFinished: {
                    _newDoc.username = _textFieldUsername.text
                }
            }
            TextField{
                id: _textFieldPassword
                placeholderText: "Password"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                echoMode: TextField.Password
                onEditingFinished: {
                    _newDoc.password = _textFieldPassword.text
                }
            }
            TextField{
                id: _textFieldConfirmPassword
                placeholderText: "Confirm Password"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                echoMode: TextField.Password
            }
            GroupBox{
                id: _groupBox
                title: "Specialization Fields"
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                Layout.minimumHeight: 200

               ListView{
                   anchors.fill: parent
                   model: _specializationFielsListModel
                   spacing: 10
                   delegate: RowLayout{

                       CheckBox{
                           id: _checkbox
                           Layout.alignment: Qt.AlignVCenter
                           onCheckedChanged: {
                               if(_checkbox.checked){
                                   _newDoc.addField(model.Id)
                               }else{
                                   _newDoc.removeField(model.Id)
                               }
                           }
                       }
                       Text{
                           text: model.Name
                           Layout.alignment: Qt.AlignVCenter
                           Layout.leftMargin: 10
                           font.pixelSize: 11
                       }
                   }
               }
            }

            Item{Layout.fillWidth: true}
            Button{
                id: _submitButton
                text: "Submit"
                font.pixelSize: 11
                Layout.fillWidth: true
                Layout.leftMargin: 20
                Layout.rightMargin: 20
                enabled: (_textFieldPassword.text.length > 0 )&& (_textFieldConfirmPassword.text === _textFieldPassword.text)
                onClicked: {
                    _specializationFielsListModel.newDoctor(_newDoc.fullname,_newDoc.username,_newDoc.password,_newDoc.specializationFields);
                }

            }


        }
    }


    SpecializationFieldListModel{
        id: _specializationFielsListModel

    }

    Component.onCompleted: {
        _specializationFielsListModel.fetchSpecializationFields()
    }

    Connections{
        target: _specializationFielsListModel
        ignoreUnknownSignals: true
        function onDoctorSavedSuccessfully(){
            dialogManager.closeDialog()
        }
    }

}
