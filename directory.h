#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "mail.h"

#include <QStandardItem>
#include <QStandardItemModel>
#include <QVector>
#include <QString>

#include <memory>

class Directory : public QStandardItemModel, public QStandardItem
{
public:
    Directory();
    Directory(const QString &name);

private:
    QVector<std::shared_ptr<Mail>> mails;
};

#endif // DIRECTORY_H
