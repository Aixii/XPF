#ifndef IR_SETTINGDIALOG_H
#define IR_SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class IR_SettingDialog;
}

class IR_SettingDialog : public QDialog {
    Q_OBJECT

public:
    explicit IR_SettingDialog(QWidget* parent = nullptr);
    ~IR_SettingDialog();

    void init();

signals:
    void sigSettingChanged();

    // QWidget interface
protected:
    void showEvent(QShowEvent* event) override;

private:
    void resetInfo();
    void apply();
    void closeDialog();

private slots:
    void on_pushButton_apply_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_cancle_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::IR_SettingDialog* ui;
};

#endif // IR_SETTINGDIALOG_H
