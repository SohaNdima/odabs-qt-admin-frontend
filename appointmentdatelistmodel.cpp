#include "appointmentdatelistmodel.h"
#include "appointmentdate.h"
#include "appointmentdetailslistmodel.h"
#include "networkmanager.h"
#include "authentication.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

AppointmentDateListModel::AppointmentDateListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

AppointmentDateListModel::~AppointmentDateListModel()
{
    clear();
}

void AppointmentDateListModel::clear()
{
    for(AppointmentDate* d: m_appointmentDates){
        delete d;
    }
    m_appointmentDates.clear();

}

void AppointmentDateListModel::changeModel(const QVector<AppointmentDate *> &appointmentDates)
{
    beginResetModel();
    clear();
    for(AppointmentDate* d: appointmentDates){
        m_appointmentDates.push_back(d);
    }
    endResetModel();
}

AppointmentDetailsListModel *AppointmentDateListModel::extractAppointmentDetailsListModel(const int &index)
{
    return m_appointmentDates.at(index)->appointments();
}

AppointmentDetailsListModel *AppointmentDateListModel::extractAppointmentDetailsListModelByDate(const QDate &date)
{
    for(AppointmentDate* d: m_appointmentDates){
        if(d->date().dayOfYear() == date.dayOfYear() && d->date().month() == date.month() && d->date().year() == date.year()){
            return d->appointments();
        }
    }
    return nullptr;
}

void AppointmentDateListModel::fetchAppointments(const QString &key, const QString &value)
{
    QString url = QString("%1/api/v1/appointments?key=%2&searchValue=%3").arg(NetworkManager::instance().baseUrl()).arg(key).arg(value);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", QVariant(Authentication::instance().token()).toByteArray());

    QNetworkReply *reply = NetworkManager::instance().get(request);
    connect(reply, &QNetworkReply::finished,this,&AppointmentDateListModel::onAppointmentsFetched);

}


int AppointmentDateListModel::getExistingDateIndex(const QDate &date)
{
    int count =0;
    for(AppointmentDate *appointmentDate : m_appointmentDates){
        if(appointmentDate->date() == date){
            return count;
        }
        count++;
    }
    return -1;
}

QString evaluateDuration(const int &minutes){


    int hrs = minutes / 60;
    int mins = minutes % 60;

    if(hrs == 0){
        return QString("%1 mins").arg(mins);
    }
    if(hrs != 0 && mins == 0){
        return QString("%1 hrs").arg(hrs);
    }

    return QString("%1 hrs %2 mins").arg(hrs).arg(mins);

}

void AppointmentDateListModel::onAppointmentsFetched()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)==200){

        beginResetModel();
        clear();
        QJsonArray appointmentsArray = QJsonDocument::fromJson(reply->readAll()).array();

        for(const QJsonValue &v : appointmentsArray){

            QJsonObject appointmentObject = v.toObject();
            QJsonObject appointmentTimeObject = appointmentObject.value("appointmentTime").toObject();
            QJsonObject doctor = appointmentObject.value("doctor").toObject();
            QJsonObject patient = appointmentObject.value("patient").toObject();
            QJsonObject appointmentType = appointmentObject.value("appointmentType").toObject();

            QDateTime date = QDateTime::fromString(appointmentTimeObject.value("date").toString(),"dd-MM-yyyy HH:mm");

          //Check if therz an already existing appointment date

            int existingIndex = getExistingDateIndex(QDate(date.date()));
            if(existingIndex <0){
                //Appointment Date does not exist
                //Create Appointment Date

                AppointmentDate *appointmentDate = new AppointmentDate;
                appointmentDate->setDate(QDate(date.date()));

                AppointmentDetails * appointmentDetails = new AppointmentDetails;
                appointmentDetails->patient = patient.value("fullname").toString();
                appointmentDetails->appointmentType = appointmentType.value("name").toString();
                appointmentDetails->appointmentStatus = appointmentObject.value("appointmentStatus").toString();
                appointmentDetails->duration = appointmentTimeObject.value("duration").toInt();
                appointmentDetails->time = date.time();
                appointmentDetails->endTime = appointmentDetails ->time.addSecs(appointmentTimeObject.value("duration").toInt() * 60);
                appointmentDetails->isMorning = date.time() < QTime(12,00);

                QVector<AppointmentDetails*> v;
                v.push_back(appointmentDetails);
                emit dateHasAppointments(appointmentDate->date());
                appointmentDate->appointments()->setAppointmentDetails(v);

                m_appointmentDates.push_back(appointmentDate);


            }else{
                //AppointmentDate exists
                //Fetch it by index

                AppointmentDate *appointmentDate = m_appointmentDates.at(existingIndex);

                AppointmentDetails * appointmentDetails = new AppointmentDetails;
                appointmentDetails->patient = patient.value("fullname").toString();
                appointmentDetails->appointmentType = appointmentType.value("name").toString();
                appointmentDetails->appointmentStatus = appointmentObject.value("appointmentStatus").toString();
                appointmentDetails->duration = appointmentTimeObject.value("duration").toInt();
                appointmentDetails->time = date.time();
                appointmentDetails->endTime = appointmentDetails ->time.addSecs(appointmentTimeObject.value("duration").toInt() * 60);
                appointmentDetails->isMorning = date.time() < QTime(12,00);

                appointmentDate->appointments()->addAppointmentDetails(appointmentDetails);

            }

        }

        endResetModel();

    }else{
        qDebug() << reply->errorString();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() << reply->readAll();
    }
    reply->deleteLater();
}

int AppointmentDateListModel::rowCount(const QModelIndex &parent) const
{
    return m_appointmentDates.size();
}

QVariant AppointmentDateListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    switch(role){
        case DateRole:
        return m_appointmentDates.at(row)->date();
    case NumberOfAppointmentsRole:
        return m_appointmentDates.at(row)->appointments()->appointmentDetails().size();

    }
    return QVariant();
}

QHash<int, QByteArray> AppointmentDateListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names.insert(DateRole,"Date");
    names.insert(NumberOfAppointmentsRole,"NumberOfAppointments");
    return names;
}
