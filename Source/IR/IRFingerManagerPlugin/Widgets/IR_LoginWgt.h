#ifndef IR_LOGINWGT_H
#define IR_LOGINWGT_H

//#include "IR_FingerLoginDialog.h"
#include <QFrame>
#include <QWidget>

namespace Ui {
class IR_LoginWgt;
}

class IR_LoginWgt : public QWidget {
    Q_OBJECT

public:
    explicit IR_LoginWgt(QWidget* parent = nullptr);
    ~IR_LoginWgt();

    void init();

    void showMask(bool);

signals:
    void sigLoginSucessed();
    void sigLogin(const QString& username, const QString& password);
    void sigRegister();

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_Register_clicked();

    void on_pushButton_FingerLogin_clicked();

private:
    Ui::IR_LoginWgt* ui;
    //    IR_FingerLoginDialog* m_FingerLogin;

    QFrame* m_MaskFrame; // 将本页变为背景的掩盖图层

    // QObject interface
public:
    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // IR_LOGINWGT_H
