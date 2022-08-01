#include "dialogmanager.h"




DialogManager &DialogManager::instance()
{
    static DialogManager dialogManager;
    return dialogManager;
}

void DialogManager::openDialog(const QString &dialog)
{
    this->setCurrentDialog(dialog);
    this->setIsOpen(true);

}

void DialogManager::closeDialog()
{
    this->setIsOpen(false);
}

DialogManager::DialogManager()
{

}

DialogManager::DialogManager(const DialogManager &)
{

}

DialogManager::~DialogManager()
{

}

bool DialogManager::isOpen() const
{
    return m_isOpen;
}

void DialogManager::setIsOpen(bool newIsOpen)
{
    if (m_isOpen == newIsOpen)
        return;
    m_isOpen = newIsOpen;
    emit isOpenChanged();
}

const QString &DialogManager::currentDialog() const
{
    return m_currentDialog;
}

void DialogManager::setCurrentDialog(const QString &newCurrentDialog)
{
    if (m_currentDialog == newCurrentDialog)
        return;
    m_currentDialog = newCurrentDialog;
    emit currentDialogChanged();
}
