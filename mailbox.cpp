#include "mailbox.h"

#include "directoryitem.h"

MailBox::MailBox()
    : model(std::make_shared<QStandardItemModel>())
{}

int MailBox::mailCounter = 0;

std::shared_ptr<QStandardItemModel> MailBox::getModel() {
    return model;
}

void MailBox::addMail(const std::shared_ptr<Mail> &mail, Directory directory) {
    auto dirIndex = static_cast<int>(directory);
    auto dir = static_cast<DirectoryItem*>(model->item(dirIndex));
    dir->addMail(mail);
}

void MailBox::moveMail(const QModelIndex &sourceIndex, Directory sourceDir, Directory destDir) {
    auto srcIndex = static_cast<int>(sourceDir);
    auto sDir = static_cast<DirectoryItem*>(model->item(srcIndex));

    auto dstIndex = static_cast<int>(destDir);
    auto dDir = static_cast<DirectoryItem*>(model->item(dstIndex));

    auto mail = sDir->getMail(sourceIndex.row());
    dDir->addMail(mail);
    sDir->removeMail(sourceIndex);
}

QString MailBox::getDirectoryName(Directory dir) {
    switch (dir) {
    case Directory::inbox:
        return "Inbox";
    case Directory::archived:
        return "Archived";
    case Directory::sent:
        return "Sent";
    case Directory::spam:
        return "Spam";
    case Directory::removed:
        return "Removed";

    default:
        return "";
    }
}


void MailBox::loadExampleData() {
    QStringList labels = {"topic", "sender", "time"};

    auto inbox = new DirectoryItem("inbox");
    inbox->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        inbox->addMail(loadExampleMail());
    model->appendRow(inbox);

    auto archived = new DirectoryItem("archived");
    archived->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        archived->addMail(loadExampleMail());
    model->appendRow(archived);

    auto sent = new DirectoryItem("sent");
    sent->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        sent->addMail(loadExampleMail());
    model->appendRow(sent);

    auto drafts = new DirectoryItem("drafts");
    drafts->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        drafts->addMail(loadExampleMail());
    model->appendRow(drafts);

    auto spam = new DirectoryItem("spam");
    spam->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        spam->addMail(loadExampleMail());
    model->appendRow(spam);

    auto removed = new DirectoryItem("removed");
    removed->getModel()->setHorizontalHeaderLabels(labels);
    for (int i = 0; i < 8; ++i)
        removed->addMail(loadExampleMail());
    model->appendRow(removed);

}

std::shared_ptr<Mail> MailBox::loadExampleMail() {
    auto mail = std::make_shared<Mail>();

    mail->setSender("sender" + QString::number(mailCounter));
    mail->setTopic("topic" + QString::number(mailCounter));
    mail->setContent("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus eleifend ornare eros vel blandit. Morbi aliquam varius tortor eget aliquam. Aliquam sed feugiat arcu, eget condimentum tortor. Mauris maximus orci mi, id interdum nibh blandit in. Maecenas vulputate mi lorem, sit amet vestibulum risus elementum vel. Nullam sodales sapien sed eleifend posuere. Morbi ultricies nulla tortor. Aliquam laoreet faucibus porttitor. Aliquam egestas eros neque. Mauris varius lectus eu elit cursus dapibus. Sed dapibus leo quis sodales suscipit. In tincidunt lorem mollis, sodales est vitae, finibus quam. Donec lacinia orci id ligula blandit luctus.");
    QDate date(1984 + mailCounter, 5, 17);
    QDateTime dt(date);
    mail->setSendTime(dt);
    ++mailCounter;
    return mail;
}
