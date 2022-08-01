#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QObject>

class Authentication : public QObject
{
    Q_OBJECT
public:
    static Authentication& instance();
    bool authenticated() const;
    void setAuthenticated(bool newAuthenticated);

    Q_INVOKABLE void login(const QString& username, const QString& password);
    Q_INVOKABLE void logout();

    const QString &name() const;
    void setName(const QString &newName);
    const QString &token() const;
    void setToken(const QString &newToken);

private slots:
    void onLoginRequestFinished();

signals:
    void authenticatedChanged();

    void nameChanged();
    void tokenChanged();

private:
    Authentication();
    Authentication(const Authentication&);
    ~Authentication();
    Authentication& operator=(const Authentication&);

    bool m_authenticated;
    QString m_name;
    QString m_token;



    Q_PROPERTY(bool authenticated READ authenticated WRITE setAuthenticated NOTIFY authenticatedChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
};

#endif // AUTHENTICATION_H
