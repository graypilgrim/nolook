#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mail.h"

#include <QMainWindow>
#include <QStandardItemModel>

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

private:
    static int mailCounter;

    void loadExampleData();
    std::shared_ptr<Mail> loadExampleMail();

    Ui::MainWindow *ui;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
