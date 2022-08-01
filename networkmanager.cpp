#include "networkmanager.h"


NetworkManager &NetworkManager::instance()
{
    static NetworkManager networkManager;
    return networkManager;
}

NetworkManager::NetworkManager()
{

}

NetworkManager::NetworkManager(const NetworkManager &)
{

}

NetworkManager::~NetworkManager()
{

}

const QString &NetworkManager::baseUrl() const
{
    return m_baseUrl;
}

void NetworkManager::setBaseUrl(const QString &newBaseUrl)
{
    if (m_baseUrl == newBaseUrl)
        return;
    m_baseUrl = newBaseUrl;
    emit baseUrlChanged();
}
