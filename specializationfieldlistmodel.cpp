#include "specializationfieldlistmodel.h"
#include "networkmanager.h"
#include "authentication.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include "notificationmanager.h"

SpecializationFieldListModel::SpecializationFieldListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

SpecializationFieldListModel::~SpecializationFieldListModel()
{
    clear();
}

void SpecializationFieldListModel::clear()
{
    for(SpecializationField* f: m_specializationFields){
        delete f;
    }
    m_specializationFields.clear();
}

void SpecializationFieldListModel::fetchSpecializationFields()
{

    QString url = QString("%1/api/v1/specialization-fields").arg(NetworkManager::instance().baseUrl());
    QNetworkRequest request(url);
    request.setRawHeader("Authorization",QVariant(Authentication::instance().token()).toByteArray());
    QNetworkReply *reply = NetworkManager::instance().get(request);
    connect(reply, &QNetworkReply::finished, this, &SpecializationFieldListModel::onSpecializationFieldsFetchComplete);

}

void SpecializationFieldListModel::newDoctor(const QString &fullname, const QString &username, const QString &password, const QVariantList &list)
{
    QString url = QString("%1/api/v1/registration/doctors").arg(NetworkManager::instance().baseUrl());
    QNetworkRequest request(url);
    request.setRawHeader("Authorization",QVariant(Authentication::instance().token()).toByteArray());
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject object;
    object.insert("fullname",QJsonValue(fullname));
    object.insert("username",QJsonValue(username));
    object.insert("password",QJsonValue(password));
    QJsonArray array;
    for(const QVariant &v: list){
        array.append(v.toJsonValue());
    }
    object.insert("fieldsOfSpecialization",array);

    QNetworkReply *reply = NetworkManager::instance().post(request,QJsonDocument(object).toJson());
    connect(reply, &QNetworkReply::finished, this, &SpecializationFieldListModel::onNewDoctorCreationRequestComplete);



}



void SpecializationFieldListModel::onSpecializationFieldsFetchComplete()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if(!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)==200){
        beginResetModel();
        clear();


        for(const QJsonValue &v : QJsonDocument::fromJson(reply->readAll()).array()){
            QJsonObject object = v.toObject();
            SpecializationField *specializationField = new SpecializationField;
            specializationField->id = object.value("id").toString();
            specializationField->name = object.value("field").toString();
            m_specializationFields.push_back(specializationField);
        }
        endResetModel();

    }else{
        qDebug() << reply->errorString();

    }
    reply->deleteLater();
    
}

void SpecializationFieldListModel::onNewDoctorCreationRequestComplete()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200){
        emit doctorSavedSuccessfully();
        emit NotificationManager::instance().showNotification(NotificationManager::Success,"New Doctor Added!");
    }else{
        qDebug() << reply->errorString();
        emit NotificationManager::instance().showNotification(NotificationManager::Failure,"Failed to save doctor!");
    }
    reply->deleteLater();
}

int SpecializationFieldListModel::rowCount(const QModelIndex &parent) const
{
    return m_specializationFields.size();
}

QVariant SpecializationFieldListModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    switch(role){
        case IdRole:
        return m_specializationFields.at(row)->id;
    case NameRole:
        return m_specializationFields.at(row)->name;

    }
    return QVariant();
}

QHash<int, QByteArray> SpecializationFieldListModel::roleNames() const
{
    QHash<int,QByteArray> names ;
    names.insert(IdRole,"Id");
    names.insert(NameRole,"Name");
    return names;
}
