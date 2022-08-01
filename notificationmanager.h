#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>

class NotificationManager : public QObject
{
    Q_OBJECT


public:
    enum NotificationStatus{
        Success,Failure,Information
    };

    static NotificationManager& instance();

    bool notificationOpen() const;
    void setNotificationOpen(bool newNotificationOpen);

signals:
    void showNotification(const NotificationStatus& status, const QString& message);
    void closeNotification();

    void notificationOpenChanged();


private slots:
    void onNotificationOpened();
    void onNotificationClosed();
private:
    NotificationManager();
    NotificationManager(const NotificationManager&);
    ~NotificationManager();
    NotificationManager& operator=(const NotificationManager&);

    bool m_notificationOpen;

    Q_PROPERTY(bool notificationOpen READ notificationOpen WRITE setNotificationOpen NOTIFY notificationOpenChanged)
};

#endif // NOTIFICATIONMANAGER_H
