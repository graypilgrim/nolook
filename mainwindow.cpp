#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"

#include <QAction>
#include <QIcon>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{}

MainWindow::MainWindow(QWidget *parent, const std::shared_ptr<MailBox> &mailBox, const std::shared_ptr<Configuration> &configuration)
    : QMainWindow(parent), mailBox(mailBox), configuration(configuration), currentDirectory(Directory::inbox)
{
    ui.reset(new Ui::MainWindow);
    ui->setupUi(this);

    ui->mailDirectory->setModel(mailBox->getModel().get());
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(0));
    ui->directoryContent->setModel(dir->getModel().get());

    bindSignals();
    createMenus();
    createActions();
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadDirectory(const QModelIndex &index) {
    auto i = index.row();
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(i));
    ui->directoryContent->setModel(dir->getModel().get());
    currentDirectory = static_cast<Directory>(i);

    setButtonsAvailability();
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

    ui->mailContent->clear();

    if (currentDirectory != Directory::removed) {
        mailBox->moveMail(selected[0], currentDirectory, Directory::removed);
        return;
    }

    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    dir->removeMail(selected[0]);
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

void MainWindow::sendDraft() {
    auto selected = ui->directoryContent->selectionModel()->selectedIndexes();

    if (selected.size() != 3)
        return;

    int dirIndex = static_cast<int>(currentDirectory);
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(dirIndex));
    auto baseMail = dir->getMail(selected[0].row());
    dir->removeMail(selected[0]);

    newMailWindow.reset(new NewMailWindow(this, mailBox));
    newMailWindow->setMail(baseMail);
    newMailWindow->show();
}

void MainWindow::settings() {
    settingsDialog.reset(new SettingsDialog(this, configuration));
    settingsDialog->exec();
}

void MainWindow::bindSignals() {
    QObject::connect(ui->mailDirectory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadDirectory(const QModelIndex&)));
    QObject::connect(ui->directoryContent, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadMailContent(const QModelIndex&)));
    QObject::connect(ui->deleteMailButton, SIGNAL(clicked()), this, SLOT(removeMail()));
    QObject::connect(ui->newMailButton, SIGNAL(clicked()), this, SLOT(newMail()));
    QObject::connect(ui->respondButton, SIGNAL(clicked()), this, SLOT(newRespond()));
    QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendDraft()));
    QObject::connect(ui->settingsButton, SIGNAL(clicked()), this, SLOT(settings()));
}

void MainWindow::createMenus() {
    moveMenu = std::make_shared<QMenu>();
    ui->moveButton->setMenu(moveMenu.get());
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
    auto result = "from: " + mail->getSender() + "\n";
    result += "topic:" + mail->getTopic() + "\n";
    result += "sent time:" + mail->getSendTime().toString("dd-MM-yy") + "\n";
    result += mail->getContent();
    return result;
}

void MainWindow::setButtonsAvailability()
{
    if ( currentDirectory != Directory::drafts)
        ui->sendButton->setEnabled(false);
    else
        ui->sendButton->setEnabled(true);

    if ( currentDirectory == Directory::sent || currentDirectory == Directory::drafts) {
        ui->moveButton->setEnabled(false);
        ui->respondButton->setEnabled(false);
    } else {
        ui->moveButton->setEnabled(true);
        ui->respondButton->setEnabled(true);
    }

    switch (currentDirectory) {
    case Directory::inbox:
    case Directory::archived:
        ui->respondButton->setEnabled(true);
        ui->moveButton->setEnabled(true);
        ui->sendButton->setEnabled(false);
        break;

    case Directory::spam:
    case Directory::removed:
        ui->respondButton->setEnabled(false);
        ui->moveButton->setEnabled(true);
        ui->sendButton->setEnabled(false);
        break;

    case Directory::sent:
        ui->respondButton->setEnabled(false);
        ui->moveButton->setEnabled(false);
        ui->sendButton->setEnabled(false);
        break;

    case Directory::drafts:
        ui->respondButton->setEnabled(false);
        ui->moveButton->setEnabled(false);
        ui->sendButton->setEnabled(true);
        break;

    default:
        break;
    }
}

