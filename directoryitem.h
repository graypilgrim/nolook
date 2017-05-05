#ifndef MAILITEM_H
#define MAILITEM_H

#include <mail.h>

#include <QStandardItem>
#include <QList>

#include <memory>

class DirectoryItem : public QStandardItem
{
public:
    DirectoryItem(const QString & text);
    void addMail(const std::shared_ptr<Mail> &mail);
    void removeMail(const std::shared_ptr<Mail> &mail);

private:
    QList<std::pair<std::shared_ptr<Mail>, QList<QStandardItem*>>> mails;
};

#endif // MAILITEM_H
