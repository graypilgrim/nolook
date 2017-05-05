#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), model(new QStandardItemModel)
{
    ui->setupUi(this);

    loadExampleData();
    ui->mailDirectory->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

int MainWindow::mailCounter = 0;

void MainWindow::loadExampleData() {
    auto inbox = new DirectoryItem("inbox");
    for (int i = 0; i < 8; ++i)
        inbox->addMail(loadExampleMail());
    model->appendRow(inbox);

    auto spam = new DirectoryItem("spam");
    for (int i = 0; i < 8; ++i)
        spam->addMail(loadExampleMail());
    model->appendRow(spam);
}

std::shared_ptr<Mail> MainWindow::loadExampleMail() {
    auto mail = std::make_shared<Mail>();

    mail->setSender("sender" + QString::number(mailCounter));
    mail->setTopic("topic" + QString::number(mailCounter));
    QDate date(1995, 5, 17);
    QDateTime dt(date);
    mail->setSendTime(dt);

    return mail;
}

