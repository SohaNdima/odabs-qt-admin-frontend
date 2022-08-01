#ifndef APPOINTMENTDATELISTMODEL_H
#define APPOINTMENTDATELISTMODEL_H

#include <QAbstractListModel>
#include <QVector>


class AppointmentDate;
class AppointmentDetailsListModel;
class AppointmentDateListModel : public QAbstractListModel
{
    Q_OBJECT

    enum AppointmentDateRole{
        DateRole = Qt::UserRole + 1, NumberOfAppointmentsRole
    };

public:
    explicit AppointmentDateListModel(QObject *parent = nullptr);
    ~AppointmentDateListModel();
    void clear();
    void changeModel(const QVector<AppointmentDate*>& appointmentDates);

    Q_INVOKABLE AppointmentDetailsListModel* extractAppointmentDetailsListModel(const int &index);
    Q_INVOKABLE AppointmentDetailsListModel* extractAppointmentDetailsListModelByDate(const QDate &date);
    Q_INVOKABLE void fetchAppointments(const QString &key, const QString &value);
    int getExistingDateIndex(const QDate &date);


signals:

    void dateHasAppointments(const QDate& date);
private slots:
    void onAppointmentsFetched();

private:
    QVector<AppointmentDate*> m_appointmentDates;



    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // APPOINTMENTDATELISTMODEL_H
