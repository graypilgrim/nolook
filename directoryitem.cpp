#include "directoryitem.h"

#include <QList>

DirectoryItem::DirectoryItem(const QString & text)
    :QStandardItem(text), model(std::make_shared<QStandardItemModel>())
{}

void DirectoryItem::addMail(const std::shared_ptr<Mail> &mail) {
    QList<QStandardItem*> list;
    list.append(new QStandardItem(mail->getTopic()));
    list.append(new QStandardItem(mail->getSender()));
    auto date = mail->getSendTime().toString("hh:mm dd-MM-yyyy");
    list.append(new QStandardItem(date));

    mails.push_back(mail);
    model->appendRow(list);
}

void DirectoryItem::removeMail(const std::shared_ptr<Mail> &mail) {
    int toRemove = -1;
    for (int i = 0; i < mails.size(); ++i)
        if (mails[i].get() == mail.get()) {
            toRemove = i;
            break;
        }

    if (toRemove >= 0) {
        mails.removeAt(toRemove);
        model->removeRow(toRemove);
    }
}

std::shared_ptr<QStandardItemModel> DirectoryItem::getModel() {
    return model;
}

std::shared_ptr<Mail> DirectoryItem::getMail(int index) {
    return mails[index];
}
