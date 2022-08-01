#include "appointmentdetailslistmodel.h"

AppointmentDetailsListModel::AppointmentDetailsListModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

AppointmentDetailsListModel::~AppointmentDetailsListModel()
{
    clear();
}

const QVector<AppointmentDetails *> &AppointmentDetailsListModel::appointmentDetails() const
{
    return m_appointmentDetails;
}

void AppointmentDetailsListModel::addAppointmentDetails(AppointmentDetails *a)
{
    m_appointmentDetails.push_back(a);
}

void AppointmentDetailsListModel::setAppointmentDetails(const QVector<AppointmentDetails *> &newAppointmentDetails)
{
    if (m_appointmentDetails == newAppointmentDetails)
        return;
    m_appointmentDetails = newAppointmentDetails;
    emit appointmentDetailsChanged();
}

void AppointmentDetailsListModel::clear()
{
    for(AppointmentDetails * a : m_appointmentDetails){
        delete a;
    }
    m_appointmentDetails.clear();
}

void AppointmentDetailsListModel::resetModel(const QVector<AppointmentDetails *> &v)
{
    beginResetModel();
    clear();
    for(AppointmentDetails* a: v){
        m_appointmentDetails.push_back(a);
    }
    endResetModel();
}

int AppointmentDetailsListModel::rowCount(const QModelIndex &parent) const
{
    return m_appointmentDetails.size();
}

QString formatTime(const QTime& time){
    int hour = time.hour();
    int minute = time.minute();
    QString timeOfDay = hour <= 12 ? "AM":"PM";
    QString resolvedHour= hour < 10 ? QString("0%1").arg(hour) : QString("%1").arg(hour);
    QString resolvedMinute = minute < 10 ? QString("0%1").arg(minute): QString("%1").arg(minute);
    return QString("%1:%2 %3").arg(resolvedHour).arg(resolvedMinute).arg(timeOfDay);
}

QVariant AppointmentDetailsListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    switch(role){
        case PatientRole:
        return m_appointmentDetails.at(row)->patient;
    case AppointmentTypeRole:
        return m_appointmentDetails.at(row)->appointmentType;
    case AppointmentStatusRole:
        return m_appointmentDetails.at(row)->appointmentStatus;
    case DurationRole:
        return m_appointmentDetails.at(row)->duration;
    case SelectedRole:
        return m_appointmentDetails.at(row)->selected;
    case TimeRole:
        return formatTime(m_appointmentDetails.at(row)->time);
    case IsMorningRole:
        return m_appointmentDetails.at(row)->isMorning;
    case EndTimeRole:
        return formatTime(m_appointmentDetails.at(row)->endTime);
    }
    return QVariant();
}

QHash<int, QByteArray> AppointmentDetailsListModel::roleNames() const
{
    QHash<int, QByteArray> names ;
    names.insert(PatientRole, "Patient");
    names.insert(AppointmentTypeRole, "AppointmentType");
    names.insert(AppointmentStatusRole, "AppointmentStatus");
    names.insert(DurationRole, "Duration");
    names.insert(SelectedRole, "Selected");
    names.insert(TimeRole, "Time");
    names.insert(IsMorningRole,"IsMorning");
    names.insert(EndTimeRole,"EndTime");
    return names;
}
