#include "mainwindow.h"
#include "mailbox.h"
#include "configuration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto mailBox = std::make_shared<MailBox>();
    mailBox->loadExampleData();
    auto configuration = std::make_shared<Configuration>();
    configuration->loadDefaultData();

    MainWindow w(nullptr, mailBox, configuration);
    w.show();

    return a.exec();
}
