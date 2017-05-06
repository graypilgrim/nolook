#include "newmailwindow.h"
#include "ui_newmailwindow.h"

NewMailWindow::NewMailWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.reset(new Ui::NewMailWindow);
    ui->setupUi(this);
}

NewMailWindow::NewMailWindow(QWidget *parent, const std::shared_ptr<MailBox> &mailBox)
    : QMainWindow(parent), mailBox(mailBox)
{
    ui.reset(new Ui::NewMailWindow);
    ui->setupUi(this);

    bindSignals();
}

NewMailWindow::~NewMailWindow()
{}

void NewMailWindow::setMail(const std::weak_ptr<Mail> &mail) {
    auto m = mail.lock();
    ui->fromTextEdit->insertPlainText(m->getSender());
    ui->toTextEdit->insertPlainText(m->getRecipient());
    ui->topicTextEdit->insertPlainText(m->getTopic());
    ui->contentTextEdit->insertPlainText(m->getContent());
}

void NewMailWindow::sendMail() {
    auto mail = createMail();
    mailBox->addMail(mail, Directory::sent);
    hide();
}

void NewMailWindow::saveAsDraft() {
    auto mail = createMail();
    mailBox->addMail(mail, Directory::drafts);
    hide();
}

void NewMailWindow::cancel() {
    hide();
}

std::shared_ptr<Mail> NewMailWindow::createMail() {
    auto mail = std::make_shared<Mail>();
    mail->setSender(ui->fromTextEdit->toPlainText());
    mail->setRecipient(ui->toTextEdit->toPlainText());
    mail->setTopic(ui->topicTextEdit->toPlainText());
    mail->setContent(ui->contentTextEdit->toPlainText());
    mail->setSendTime(QDateTime::currentDateTime());

    return mail;
}

void NewMailWindow::bindSignals() {
    QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMail()));
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveAsDraft()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}
