#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mail.h"
#include "mailbox.h"
#include "newmailwindow.h"
#include "settingsdialog.h"

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
    MainWindow(QWidget *parent, const std::shared_ptr<MailBox> &mailBox, const std::shared_ptr<Configuration> &configuration);
    ~MainWindow();

public slots:
    void loadDirectory(const QModelIndex &index);
    void loadMailContent(const QModelIndex &index);
    void removeMail();
    void moveMail();
    void newMail();
    void newRespond();
    void sendDraft();
    void settings();

private:
    void bindSignals();
    void createMenus();
    void createActions();
    QString prepareMailContent(Mail *mail);
    void setButtonsAvailability();

    std::unique_ptr<Ui::MainWindow> ui;

    std::shared_ptr<MailBox> mailBox;
    std::shared_ptr<Configuration> configuration;

    std::shared_ptr<QMenu> moveMenu;
    std::unique_ptr<NewMailWindow> newMailWindow;
    std::unique_ptr<SettingsDialog> settingsDialog;

    Directory currentDirectory;

};

#endif // MAINWINDOW_H
