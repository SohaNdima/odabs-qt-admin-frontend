#ifndef APPOINTMENTDATE_H
#define APPOINTMENTDATE_H

#include <QObject>
#include <QVector>
#include <QDate>

class AppointmentDetailsListModel;

class AppointmentDate : public QObject
{
    Q_OBJECT
public:
    explicit AppointmentDate(QObject *parent = nullptr);
    ~AppointmentDate();


    const QDate &date() const;
    void setDate(const QDate &newDate);
    AppointmentDetailsListModel *appointments() const;
    void setAppointments(AppointmentDetailsListModel *newAppointments);



signals:
    void dateChanged();
    void appointmentsChanged();

    void numberOfAppointmentsChanged();

private:
    QDate m_date;
    AppointmentDetailsListModel *m_appointments;

    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
};

#endif // APPOINTMENTDATE_H
