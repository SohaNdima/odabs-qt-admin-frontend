#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    static NetworkManager& instance();

    const QString &baseUrl() const;
    void setBaseUrl(const QString &newBaseUrl);


signals:
    void baseUrlChanged();

private:
    NetworkManager();
    NetworkManager(const NetworkManager&);
    ~NetworkManager();
    NetworkManager& operator=(const NetworkManager&);

    //QString m_baseUrl = "http://localhost:12900";
    QString m_baseUrl = "https://medical-ap.herokuapp.com";

    Q_PROPERTY(QString baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)
};

#endif // NETWORKMANAGER_H
