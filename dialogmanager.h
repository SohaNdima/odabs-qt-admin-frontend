#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QObject>

class DialogManager : public QObject
{
    Q_OBJECT

public:
    static DialogManager& instance();

    Q_INVOKABLE void openDialog(const QString& dialog);
    Q_INVOKABLE void closeDialog();

    const QString &currentDialog() const;
    void setCurrentDialog(const QString &newCurrentDialog);

    bool isOpen() const;
    void setIsOpen(bool newIsOpen);

signals:
    void currentDialogChanged();

    void isOpenChanged();

private:
    DialogManager();
    DialogManager(const DialogManager&);
    ~DialogManager();
    DialogManager& operator=(const DialogManager&);

    QString m_currentDialog;
    bool m_isOpen;



    Q_PROPERTY(QString currentDialog READ currentDialog WRITE setCurrentDialog NOTIFY currentDialogChanged)
    Q_PROPERTY(bool isOpen READ isOpen WRITE setIsOpen NOTIFY isOpenChanged)
};

#endif // DIALOGMANAGER_H
