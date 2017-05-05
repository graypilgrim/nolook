#ifndef MAILBOX_H
#define MAILBOX_H

#include "mail.h"

#include <QStandardItemModel>

#include <memory>

class MailBox
{
public:
    MailBox();
    std::shared_ptr<QStandardItemModel> getModel();
    void loadExampleData();

private:
    std::shared_ptr<Mail> loadExampleMail();

    static int mailCounter;

    std::shared_ptr<QStandardItemModel> model;

};

#endif // MAILBOX_H
