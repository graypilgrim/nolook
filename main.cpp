#include "mainwindow.h"
#include "mailbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto mailBox = std::make_shared<MailBox>();
    mailBox->loadExampleData();
    MainWindow w(nullptr, mailBox);
    w.show();

    return a.exec();
}
