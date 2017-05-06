#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mail.h"
#include "mailbox.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMenu>

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
    void loadMailContent(const QModelIndex &index);
    void removeMail(bool checked = false);
    void moveMail(bool checked = false);

private:
    void bindSignals();
    void createMenus();
    void createActions();
    QString prepareMailContent(Mail *mail);

    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<MailBox> mailBox;
    std::shared_ptr<QMenu> moveMenu;

    Directory currentDirectory;

};

#endif // MAINWINDOW_H
