#include "directory.h"

Directory::Directory()
    : QStandardItemModel(), QStandardItem()
{}

Directory::Directory(const QString &name)
    : QStandardItemModel(), QStandardItem(name)
{}
