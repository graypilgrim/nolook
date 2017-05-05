#include "mailbox.h"

#include "directoryitem.h"

MailBox::MailBox()
    : model(std::make_shared<QStandardItemModel>())
{}

int MailBox::mailCounter = 0;

std::shared_ptr<QStandardItemModel> MailBox::getModel() {
    return model;
}

void MailBox::loadExampleData() {
    auto inbox = new DirectoryItem("inbox");
    for (int i = 0; i < 8; ++i)
        inbox->addMail(loadExampleMail());
    model->appendRow(inbox);

    auto archived = new DirectoryItem("archived");
    for (int i = 0; i < 8; ++i)
        archived->addMail(loadExampleMail());
    model->appendRow(archived);

    auto sent = new DirectoryItem("sent");
    for (int i = 0; i < 8; ++i)
        sent->addMail(loadExampleMail());
    model->appendRow(sent);

    auto drafts = new DirectoryItem("drafts");
    for (int i = 0; i < 8; ++i)
        drafts->addMail(loadExampleMail());
    model->appendRow(drafts);

    auto spam = new DirectoryItem("spam");
    for (int i = 0; i < 8; ++i)
        spam->addMail(loadExampleMail());
    model->appendRow(spam);

    auto removed = new DirectoryItem("removed");
    for (int i = 0; i < 8; ++i)
        removed->addMail(loadExampleMail());
    model->appendRow(removed);
}

std::shared_ptr<Mail> MailBox::loadExampleMail() {
    auto mail = std::make_shared<Mail>();

    mail->setSender("sender" + QString::number(mailCounter));
    mail->setTopic("topic" + QString::number(mailCounter));
    QDate date(1995, 5, 17);
    QDateTime dt(date);
    mail->setSendTime(dt);
    ++mailCounter;
    return mail;
}
