#ifndef MAILBOX_H
#define MAILBOX_H

#include "mail.h"

#include <QStandardItemModel>

#include <memory>

enum class DirectoryName {
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
    void moveMail(const QModelIndex &sourceIndex, DirectoryName sourceDir, DirectoryName destDir);
    void loadExampleData();

private:
    std::shared_ptr<Mail> loadExampleMail();

    static int mailCounter;

    std::shared_ptr<QStandardItemModel> model;

};

#endif // MAILBOX_H
