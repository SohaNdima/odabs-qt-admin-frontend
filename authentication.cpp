#include "authentication.h"
#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>


Authentication::Authentication()
{

}

Authentication::Authentication(const Authentication &)
{

}

Authentication::~Authentication()
{

}

const QString &Authentication::name() const
{
    return m_name;
}

void Authentication::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

const QString &Authentication::token() const
{
    return m_token;
}

void Authentication::setToken(const QString &newToken)
{
    if (m_token == newToken)
        return;
    m_token = newToken;
    emit tokenChanged();
}

void Authentication::onLoginRequestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if(!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)==200){

        this->setToken(reply->rawHeader("Authorization"));
        this->setAuthenticated(true);

        this->setName( QJsonDocument::fromJson(reply->readAll()).object().value("fullname").toString());
    }else{
        qDebug() << reply->errorString();
    }
    reply->deleteLater();
}

Authentication &Authentication::instance()
{
    static Authentication authentication;
    return authentication;
}

bool Authentication::authenticated() const
{
    return m_authenticated;
}

void Authentication::setAuthenticated(bool newAuthenticated)
{
    if (m_authenticated == newAuthenticated)
        return;
    m_authenticated = newAuthenticated;
    emit authenticatedChanged();
}

void Authentication::login(const QString &username, const QString &password)
{
    QString url = QString("%1/login").arg(NetworkManager::instance().baseUrl());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QJsonObject object;
    object.insert("username", QJsonValue(username));
    object.insert("password", QJsonValue(password));

    QNetworkReply *reply = NetworkManager::instance().post(request,QJsonDocument(object).toJson());
    connect(reply, &QNetworkReply::finished,this,&Authentication::onLoginRequestFinished);


}

void Authentication::logout()
{
    this->setToken("");
    this->setAuthenticated(false);
}
