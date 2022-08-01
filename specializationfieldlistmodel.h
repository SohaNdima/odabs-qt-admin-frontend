#ifndef SPECIALIZATIONFIELDLISTMODEL_H
#define SPECIALIZATIONFIELDLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>


struct SpecializationField{
    QString id;
    QString name;
};

struct ConsumableDoctor{
    QString fullname;
    QString username;
    QVariantList specializationFields;
};

class SpecializationFieldListModel : public QAbstractListModel
{
    Q_OBJECT

    enum SpecializationFieldRole{
        IdRole = Qt::UserRole + 1, NameRole
    };

public:
    explicit SpecializationFieldListModel(QObject *parent = nullptr);
    ~SpecializationFieldListModel();

    void clear();

    Q_INVOKABLE void fetchSpecializationFields();
    Q_INVOKABLE void newDoctor(const QString &fullname,const QString &username, const QString &password,const QVariantList &list);

signals:
    void doctorSavedSuccessfully();
private slots:
    void onSpecializationFieldsFetchComplete();
    void onNewDoctorCreationRequestComplete();

private:
    QVector<SpecializationField*>m_specializationFields;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // SPECIALIZATIONFIELDLISTMODEL_H
