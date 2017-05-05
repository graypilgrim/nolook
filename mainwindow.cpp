#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directoryitem.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.reset(new Ui::MainWindow);
    mailBox.reset(new MailBox);
    mailBox->loadExampleData();

    ui->setupUi(this);

    ui->mailDirectory->setModel(mailBox->getModel().get());
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(0));
    ui->directoryContent->setModel(dir->getModel().get());
    QObject::connect(ui->mailDirectory, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadDirectory(QModelIndex)) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadDirectory(const QModelIndex &index) {
    auto i = index.row();
    auto dir = static_cast<DirectoryItem*>(mailBox->getModel()->item(i));
    ui->directoryContent->setModel(dir->getModel().get());

    std::cout << "index: " << i << std::endl;
}

