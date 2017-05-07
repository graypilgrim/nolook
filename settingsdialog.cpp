#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.reset(new Ui::SettingsDialog);
    ui->setupUi(this);
}

SettingsDialog::SettingsDialog(QWidget *parent, const std::shared_ptr<Configuration> &configuration)
    : QDialog(parent), configuration(configuration)
{
    ui.reset(new Ui::SettingsDialog);
    ui->setupUi(this);

    auto pop3Int = static_cast<int>(IncomingMailProtocol::POP3);
    ui->inProtocolBox->addItem(configuration->getProtocolName(IncomingMailProtocol::POP3), pop3Int);
    auto imapInt = static_cast<int>(IncomingMailProtocol::IMAP4);
    ui->inProtocolBox->addItem(configuration->getProtocolName(IncomingMailProtocol::IMAP4), imapInt);

    fillFields();

    bindSignals();
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::fillFields()
{
    ui->addressLine->setText(configuration->getAddress());
    ui->passLine->setText(configuration->getPassword());

    ui->inUsernameLine->setText(configuration->getInUsername());
    ui->inPassLine->setText(configuration->getInPassword());
    ui->inAddressLine->setText(configuration->getInServer());
    ui->inPortLine->setText(QString::number(configuration->getInPort()));
    auto inProtocolIndex = ui->inProtocolBox->findData(static_cast<int>(configuration->getInProtocol()));
    ui->inProtocolBox->setCurrentIndex(inProtocolIndex);

    ui->outUsernameLine->setText(configuration->getOutUsername());
    ui->outPassLine->setText(configuration->getOutPassword());
    ui->outAddressLine->setText(configuration->getOutServer());
    ui->outPortLine->setText(QString::number(configuration->getOutPort()));
}

void SettingsDialog::save()
{
    configuration->setAddress(ui->addressLine->text());
    configuration->setPassword(ui->passLine->text());

    configuration->setInUsername(ui->inUsernameLine->text());
    configuration->setInPassword(ui->inPassLine->text());
    configuration->setInServer(ui->inAddressLine->text());
    configuration->setInPort(ui->inPortLine->text().toInt());

    auto inProtocolInt = ui->inProtocolBox->itemData(ui->inProtocolBox->currentIndex());
    configuration->setInProtocol(static_cast<IncomingMailProtocol>(inProtocolInt.toUInt()));

    configuration->setOutUsername(ui->outUsernameLine->text());
    configuration->setOutPassword(ui->outPassLine->text());
    configuration->setOutServer(ui->outAddressLine->text());
    configuration->setOutPort(ui->outPortLine->text().toInt());

    accept();
}

void SettingsDialog::discard()
{
    reject();
}

void SettingsDialog::bindSignals()
{
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(ui->discardButton, SIGNAL(clicked()), this, SLOT(discard()));
}
