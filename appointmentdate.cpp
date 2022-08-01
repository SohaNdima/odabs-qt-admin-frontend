#include "appointmentdate.h"
#include "appointmentdetailslistmodel.h"


AppointmentDate::AppointmentDate(QObject *parent)
{
    m_appointments = new AppointmentDetailsListModel;
}

AppointmentDate::~AppointmentDate()
{
    delete m_appointments;
}

const QDate &AppointmentDate::date() const
{
    return m_date;
}

void AppointmentDate::setDate(const QDate &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

AppointmentDetailsListModel *AppointmentDate::appointments() const
{
    return m_appointments;
}

void AppointmentDate::setAppointments(AppointmentDetailsListModel *newAppointments)
{
    if (m_appointments == newAppointments)
        return;
    m_appointments = newAppointments;
    emit appointmentsChanged();
}


