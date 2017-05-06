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

    int row = 0;

    for (auto &m : mails) {
        if (mail->getSendTime() >= m->getSendTime())
            break;
        else
            ++row;
    }
    mails.insert(row, mail);
    model->insertRow(row, list);
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

void DirectoryItem::removeMail(const QModelIndex &index) {
    mails.removeAt(index.row());
    model->removeRow(index.row());
}

std::shared_ptr<QStandardItemModel> DirectoryItem::getModel() {
    return model;
}

std::shared_ptr<Mail> DirectoryItem::getMail(int index) {
    return mails[index];
}
