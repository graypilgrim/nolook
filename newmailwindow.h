#ifndef NEWMAILWINDOW_H
#define NEWMAILWINDOW_H

#include "mailbox.h"

#include <QMainWindow>

#include <memory>

namespace Ui {
class NewMailWindow;
}

class NewMailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMailWindow(QWidget *parent = 0);
    NewMailWindow(QWidget *parent, const std::shared_ptr<MailBox> &mailBox);
    ~NewMailWindow();

    void setMail(const std::weak_ptr<Mail> &mail);

public slots:
    void sendMail();
    void saveAsDraft();

private:
    std::shared_ptr<Mail> createMail();
    void bindSignals();

    std::unique_ptr<Ui::NewMailWindow> ui;

    std::shared_ptr<MailBox> mailBox;
};

#endif // NEWMAILWINDOW_H
