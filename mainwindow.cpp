#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), currentDirectory(DirectoryName::inbox)
{
    ui.reset(new Ui::MainWindow);
    mailBox.reset(new MailBox);
    mailBox->loadExampleData();

    ui->setupUi(this);

    ui->mailDirectory->setModel(mailBox->getModel().get());
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(0));
    ui->directoryContent->setModel(dir->getModel().get());

    bindSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadDirectory(const QModelIndex &index) {
    auto i = index.row();
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(i));
    ui->directoryContent->setModel(dir->getModel().get());
    currentDirectory = static_cast<DirectoryName>(i);

    std::cout << "index: " << i << std::endl;
}

void MainWindow::loadMailContent(const QModelIndex &index) {
    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    auto mail = dir->getMail(index.row());
    ui->mailContent->clear();
    ui->mailContent->insertPlainText(prepareMailContent(mail.get()));
}

void MainWindow::removeMail(bool checked) {
    auto selected = ui->directoryContent->selectionModel()->selectedIndexes();

    if (selected.size() != 3)
        return;

    if (currentDirectory != DirectoryName::removed) {
        mailBox->moveMail(selected[0], currentDirectory, DirectoryName::removed);
        return;
    }

    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    dir->removeMail(selected[0]);
}

void MainWindow::bindSignals() {
    QObject::connect(ui->mailDirectory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadDirectory(const QModelIndex&)));
    QObject::connect(ui->directoryContent, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadMailContent(const QModelIndex&)));
    QObject::connect(ui->deleteMailButton, SIGNAL(clicked(bool)), this, SLOT(removeMail(bool)));
}

void MainWindow::createMenus() {
    moveMenu = std::make_shared<QMenu>();
}

QString MainWindow::prepareMailContent(Mail *mail) {
    auto result = mail->getSender() + " " + mail->getTopic() + " " + mail->getSendTime().toString("dd-MM-yy");
    return result;
}

