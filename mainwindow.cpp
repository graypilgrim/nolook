#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"

#include <QAction>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{}

MainWindow::MainWindow(QWidget *parent, const std::shared_ptr<MailBox> &mailBox)
    : QMainWindow(parent), mailBox(mailBox), currentDirectory(Directory::inbox)
{
    ui.reset(new Ui::MainWindow);

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

    if ( currentDirectory != Directory::drafts)
        ui->sendButton->setEnabled(false);
    else
        ui->sendButton->setEnabled(true);

    if ( currentDirectory == Directory::sent || currentDirectory == Directory::drafts)
        ui->moveButton->setEnabled(false);
    else
        ui->moveButton->setEnabled(true);

}

void MainWindow::loadMailContent(const QModelIndex &index) {
    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    auto mail = dir->getMail(index.row());
    ui->mailContent->clear();
    ui->mailContent->insertPlainText(prepareMailContent(mail.get()));
}

void MainWindow::removeMail() {
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

void MainWindow::moveMail() {
    auto selected = ui->directoryContent->selectionModel()->selectedIndexes();

    if (selected.size() != 3)
        return;

    auto act = static_cast<QAction*>(QObject::sender());
    auto dirIndex = static_cast<Directory>(act->data().toInt());
    mailBox->moveMail(selected[0], currentDirectory, dirIndex);
}

void MainWindow::newMail() {
    newMailWindow.reset(new NewMailWindow(this, mailBox));

    newMailWindow->show();
}

void MainWindow::newRespond() {
    auto selected = ui->directoryContent->selectionModel()->selectedIndexes();

    if (selected.size() != 3)
        return;

    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    auto baseMail = dir->getMail(selected[0].row());

    auto newMail = std::make_shared<Mail>();
    newMail->setRecipient(baseMail->getSender());

    newMailWindow.reset(new NewMailWindow(this, mailBox));
    newMailWindow->setMail(newMail);
    newMailWindow->show();
}

void MainWindow::bindSignals() {
    QObject::connect(ui->mailDirectory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadDirectory(const QModelIndex&)));
    QObject::connect(ui->directoryContent, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadMailContent(const QModelIndex&)));
    QObject::connect(ui->deleteMailButton, SIGNAL(clicked()), this, SLOT(removeMail()));
    QObject::connect(ui->newMailButton, SIGNAL(clicked()), this, SLOT(newMail()));
    QObject::connect(ui->respondButton, SIGNAL(clicked()), this, SLOT(newRespond()));
}

void MainWindow::createMenus() {
    moveMenu = std::make_shared<QMenu>();
}

void MainWindow::createActions() {
    auto inboxAct = new QAction(mailBox->getDirectoryName(Directory::inbox), this);
    auto data = QVariant(static_cast<int>(Directory::inbox));
    inboxAct->setData(data);
    QObject::connect(inboxAct, SIGNAL(triggered()), this, SLOT(moveMail()));
    moveMenu->addAction(inboxAct);

    auto archAct = new QAction(mailBox->getDirectoryName(Directory::archived), this);
    data = QVariant(static_cast<int>(Directory::archived));
    archAct->setData(data);
    QObject::connect(archAct, SIGNAL(triggered()), this, SLOT(moveMail()));
    moveMenu->addAction(archAct);

    auto spamAct = new QAction(mailBox->getDirectoryName(Directory::spam), this);
    data = QVariant(static_cast<int>(Directory::spam));
    spamAct->setData(data);
    QObject::connect(spamAct, SIGNAL(triggered()), this, SLOT(moveMail()));
    moveMenu->addAction(spamAct);
}

QString MainWindow::prepareMailContent(Mail *mail) {
    auto result = mail->getSender() + "\n" + mail->getTopic() + "\n" + mail->getSendTime().toString("dd-MM-yy");
    return result;
}

