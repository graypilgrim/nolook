#ifndef MAILITEM_H
#define MAILITEM_H

#include <mail.h>

#include <QStandardItem>
#include <QStandardItemModel>
#include <QList>

#include <memory>

class DirectoryItem : public QStandardItem
{
public:
    DirectoryItem(const QString &text);
    void addMail(const std::shared_ptr<Mail> &mail);
    void removeMail(const std::shared_ptr<Mail> &mail);
    void removeMail(const QModelIndex &index);
    std::shared_ptr<QStandardItemModel> getModel();
    std::shared_ptr<Mail> getMail(int index);

private:
    QList<std::shared_ptr<Mail>> mails;
    std::shared_ptr<QStandardItemModel> model;
};

#endif // MAILITEM_H
