#include "notificationmanager.h"


NotificationManager &NotificationManager::instance()
{
    static NotificationManager notificationManager;
    return notificationManager;
}

NotificationManager::NotificationManager()
{
    connect(this, &NotificationManager::showNotification,this, &NotificationManager::onNotificationOpened);
    connect(this,&NotificationManager::closeNotification,this, &NotificationManager::onNotificationClosed);
}

NotificationManager::NotificationManager(const NotificationManager &)
{

}

NotificationManager::~NotificationManager()
{

}

bool NotificationManager::notificationOpen() const
{
    return m_notificationOpen;
}

void NotificationManager::setNotificationOpen(bool newNotificationOpen)
{
    if (m_notificationOpen == newNotificationOpen)
        return;
    m_notificationOpen = newNotificationOpen;
    emit notificationOpenChanged();
}

void NotificationManager::onNotificationOpened()
{
    this->setNotificationOpen(true);
}

void NotificationManager::onNotificationClosed()
{
    this->setNotificationOpen(false);
}
