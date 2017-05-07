#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "configuration.h"

#include <QDialog>

#include <memory>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    SettingsDialog(QWidget *parent, const std::shared_ptr<Configuration> &configuration);
    ~SettingsDialog();

    void fillFields();

public slots:
    void save();
    void discard();

private:
    void bindSignals();

    std::unique_ptr<Ui::SettingsDialog> ui;
    std::shared_ptr<Configuration> configuration;
};

#endif // SETTINGSDIALOG_H
