#ifndef APPOINTMENTDETAILSLISTMODEL_H
#define APPOINTMENTDETAILSLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QTime>


struct AppointmentDetails{
    QString patient;
    QString appointmentType;
    QString appointmentStatus;
    int duration;
    QTime time;
    QTime endTime;
    bool isMorning;
    bool selected = false;
};

class AppointmentDetailsListModel : public QAbstractListModel
{
    Q_OBJECT

    enum AppointmentDetailsRole{
        PatientRole = Qt::UserRole + 1, AppointmentTypeRole, AppointmentStatusRole, DurationRole, SelectedRole, TimeRole, IsMorningRole, EndTimeRole
    };

public:
    explicit AppointmentDetailsListModel(QObject *parent = nullptr);
    ~AppointmentDetailsListModel();

    const QVector<AppointmentDetails *> &appointmentDetails() const;
    void addAppointmentDetails(AppointmentDetails * a);
    void setAppointmentDetails(const QVector<AppointmentDetails *> &newAppointmentDetails);
    void clear();
    void resetModel(const QVector<AppointmentDetails*> &v);

signals:
    void appointmentDetailsChanged();

private:
    QVector<AppointmentDetails*> m_appointmentDetails;

    Q_PROPERTY(QVector<AppointmentDetails *> appointmentDetails READ appointmentDetails WRITE setAppointmentDetails NOTIFY appointmentDetailsChanged)

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // APPOINTMENTDETAILSLISTMODEL_H
