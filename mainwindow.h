#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mail.h"
#include "mailbox.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadDirectory(const QModelIndex &index);

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<MailBox> mailBox;
};

#endif // MAINWINDOW_H
