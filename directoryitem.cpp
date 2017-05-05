#include "directoryitem.h"

#include <QList>

DirectoryItem::DirectoryItem(const QString & text)
    :QStandardItem(text)
{}

void DirectoryItem::addMail(const std::shared_ptr<Mail> &mail) {
    QList<QStandardItem*> list;
    list.append(new QStandardItem(mail->getTopic()));
    list.append(new QStandardItem(mail->getSender()));
    auto date = mail->getSendTime().toString("hh:mm dd-MM-YYYY");
    list.append(new QStandardItem(date));

    appendRow(list);
    mails.append(std::make_pair(mail, list));
}

void DirectoryItem::removeMail(const std::shared_ptr<Mail> &mail) {
    int toRemove = -1;
    for (int i = 0; i < mails.size(); ++i)
        if (mails[i].first.get() == mail.get()) {
            toRemove = i;
            break;
        }

    if (toRemove >= 0)
        mails.removeAt(toRemove);
}
