#ifndef MAILBOX_H
#define MAILBOX_H

#include "mail.h"

#include <QStandardItemModel>

#include <memory>

enum class Directory {
    inbox,
    archived,
    sent,
    drafts,
    spam,
    removed
};

class MailBox
{
public:
    MailBox();
    std::shared_ptr<QStandardItemModel> getModel();
    void addMail(const std::shared_ptr<Mail> &mail, Directory directory);
    void moveMail(const QModelIndex &sourceIndex, Directory sourceDir, Directory destDir);
    QString getDirectoryName(Directory dir);
    void loadExampleData();

private:
    std::shared_ptr<Mail> loadExampleMail();

    static int mailCounter;

    std::shared_ptr<QStandardItemModel> model;

};

#endif // MAILBOX_H
