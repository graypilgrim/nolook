#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"

#include <QAction>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), currentDirectory(Directory::inbox)
{
    ui.reset(new Ui::MainWindow);
    mailBox.reset(new MailBox);
    mailBox->loadExampleData();

    ui->setupUi(this);

    ui->mailDirectory->setModel(mailBox->getModel().get());
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(0));
    ui->directoryContent->setModel(dir->getModel().get());

    bindSignals();
    createMenus();
    createActions();
    ui->moveButton->setMenu(moveMenu.get());
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadDirectory(const QModelIndex &index) {
    auto i = index.row();
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(i));
    ui->directoryContent->setModel(dir->getModel().get());
    currentDirectory = static_cast<Directory>(i);

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

    if (currentDirectory != Directory::removed) {
        mailBox->moveMail(selected[0], currentDirectory, Directory::removed);
        return;
    }

    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    dir->removeMail(selected[0]);
    ui->mailContent->clear();
}

void MainWindow::moveMail(bool checked) {
    auto selected = ui->directoryContent->selectionModel()->selectedIndexes();

    if (selected.size() != 3)
        return;

    auto act = static_cast<QAction*>(QObject::sender());
    auto dirIndex = static_cast<Directory>(act->data().toInt());
    mailBox->moveMail(selected[0], currentDirectory, dirIndex);

}

void MainWindow::bindSignals() {
    QObject::connect(ui->mailDirectory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadDirectory(const QModelIndex&)));
    QObject::connect(ui->directoryContent, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadMailContent(const QModelIndex&)));
    QObject::connect(ui->deleteMailButton, SIGNAL(clicked(bool)), this, SLOT(removeMail(bool)));
}

void MainWindow::createMenus() {
    moveMenu = std::make_shared<QMenu>();
}

void MainWindow::createActions() {
    auto inboxAct = new QAction(mailBox->getDirectoryName(Directory::inbox), this);
    auto data = QVariant(static_cast<int>(Directory::inbox));
    inboxAct->setData(data);
    QObject::connect(inboxAct, SIGNAL(triggered(bool)), this, SLOT(moveMail(bool)));
    moveMenu->addAction(inboxAct);

    auto archAct = new QAction(mailBox->getDirectoryName(Directory::archived), this);
    data = QVariant(static_cast<int>(Directory::archived));
    archAct->setData(data);
    QObject::connect(archAct, SIGNAL(triggered(bool)), this, SLOT(moveMail(bool)));
    moveMenu->addAction(archAct);

    auto spamAct = new QAction(mailBox->getDirectoryName(Directory::spam), this);
    data = QVariant(static_cast<int>(Directory::spam));
    spamAct->setData(data);
    QObject::connect(spamAct, SIGNAL(triggered(bool)), this, SLOT(moveMail(bool)));
    moveMenu->addAction(spamAct);
}

QString MainWindow::prepareMailContent(Mail *mail) {
    auto result = mail->getSender() + "\n" + mail->getTopic() + "\n" + mail->getSendTime().toString("dd-MM-yy");
    return result;
}

