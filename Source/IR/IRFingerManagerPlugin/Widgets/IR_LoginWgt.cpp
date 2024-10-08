#include "IR_LoginWgt.h"
// #include "FingerSerialManager.h"
// #include "IRGLobalStatus.h"
// #include "UserOperator.h"
#include "ui_IR_LoginWgt.h"
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>

IR_LoginWgt::IR_LoginWgt(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_LoginWgt) {
    ui->setupUi(this);

    m_MaskFrame = new QFrame(this);
    m_MaskFrame->setStyleSheet("QFrame { background-color: rgba(0, 0, 0, 100); border: none; }");
    m_MaskFrame->move(0, 0);
    m_MaskFrame->hide();

    //    m_FingerLogin = new IR_FingerLoginDialog(this);
    //    m_FingerLogin->setModal(true);

    QWidget::setTabOrder(ui->lineEdit_UserName, ui->lineEdit_PassWord);
    QWidget::setTabOrder(ui->lineEdit_PassWord, ui->checkBox_RememberPassWord);
    QWidget::setTabOrder(ui->checkBox_RememberPassWord, ui->pushButton_Login);
    QWidget::setTabOrder(ui->pushButton_Login, ui->pushButton_FingerLogin);

    ui->label_ForgetPWD->installEventFilter(this);

    QAction* pActAccount  = new QAction(QIcon(":/resource/image/user.png"), "", this);
    QAction* pActPassword = new QAction(QIcon(":/resource/image/lock.png"), "", this);

    ui->lineEdit_UserName->addAction(pActAccount, QLineEdit::LeadingPosition);
    ui->lineEdit_PassWord->addAction(pActPassword, QLineEdit::LeadingPosition);

    ui->lineEdit_PassWord->setEchoMode(QLineEdit::Password);

    QAction* pActShow = new QAction(QIcon(":/resource/image/hide.png"), "", this);
    pActShow->setData(false);

    ui->lineEdit_PassWord->addAction(pActShow, QLineEdit::TrailingPosition);

    QObject::connect(pActShow, &QAction::triggered, this, [this, pActShow]() {
        bool flag = pActShow->data().toBool();
        if (flag) {
            pActShow->setIcon(QIcon(":/resource/image/hide.png"));
            ui->lineEdit_PassWord->setEchoMode(QLineEdit::Password);
        }
        else {
            pActShow->setIcon(QIcon(":/resource/image/show.png"));
            ui->lineEdit_PassWord->setEchoMode(QLineEdit::Normal);
        }
        pActShow->setData(!flag);
    });

    /* 指纹采集器 */

    //    FingerSerialManager* fingerManager = Singleton<FingerSerialManager>::GetInstance();

    //    QObject::connect(
    //        fingerManager, &FingerSerialManager::sigSearchPort, this, [this](bool has, QString portName) {
    //            m_HasFingerprintReader = has;
    //        },
    //        Qt::UniqueConnection);

    //    fingerManager->seachPort();
    /************/
}

IR_LoginWgt::~IR_LoginWgt() {
    delete ui;
}

void IR_LoginWgt::init() {
    //    m_FingerLogin->init();

    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("USER");
    QString usr = settings.value("usr").toString();
    QString pwd = settings.value("pwd").toString();
    if (!usr.isEmpty()) {
        ui->lineEdit_UserName->setText(usr);
        ui->lineEdit_PassWord->setText(pwd);
        ui->checkBox_RememberPassWord->setChecked(true);
        ui->pushButton_Login->setFocus();
    }
    settings.endGroup();

    //    UserOperator* userOp = Singleton<UserOperator>::GetInstance();

    //    QObject::connect(
    //        userOp, &UserOperator::sigAuthPassed, this, [this](QString opcode) {
    //            if (opcode == this->property("opcode").toString()) {
    //                emit sigLoginSucessed();

    //                QSettings settings("d.ini", QSettings::IniFormat);
    //                settings.beginGroup("USER");
    //                if (ui->checkBox_RememberPassWord->isChecked()) {

    //                    settings.setValue("usr", ui->lineEdit_UserName->text());
    //                    settings.setValue("pwd", ui->lineEdit_PassWord->text());
    //                }
    //                else {
    //                    settings.setValue("usr", "");
    //                    settings.setValue("pwd", "");
    //                }
    //                settings.endGroup();
    //            }
    //        },
    //        Qt::UniqueConnection);

    //    QObject::connect(this, &IR_LoginWgt::sigLogin, this, [this, userOp](const QString& username, const QString& password) {
    //        userOp->slotAuthUser(username, password, this->property("opcode").toString());
    //    });
    //    QObject::connect(
    //        userOp, &UserOperator::sigAuthNoPassed, this, [this](QString opcode) {
    //            if (opcode != this->property("opcode").toString()) {
    //                return;
    //            }
    //            QMessageBox::warning(this, "登录失败", "输入的账号或密码不正确", "确认");
    //        },
    //        Qt::UniqueConnection);

    //    QObject::connect(m_FingerLogin, &IR_FingerLoginDialog::rejected, this, [this]() {
    //        showMask(false);
    //    });
}

void IR_LoginWgt::showMask(bool ok) {
    if (ok) {
        QSize size = geometry().size();
        m_MaskFrame->setGeometry(0, 0, size.width(), size.height());
        m_MaskFrame->show();
        m_MaskFrame->raise();
    }
    else {
        m_MaskFrame->hide();
    }
}

void IR_LoginWgt::on_pushButton_Login_clicked() {
    QString username = ui->lineEdit_UserName->text();
    QString password = ui->lineEdit_PassWord->text();

    emit sigLogin(username, password);
}

bool IR_LoginWgt::eventFilter(QObject* watched, QEvent* event) {
    if (watched == ui->label_ForgetPWD) {
        if (event->type() == QEvent::Enter) {
            QFont font = ui->label_ForgetPWD->font();
            font.setUnderline(true);
            ui->label_ForgetPWD->setFont(font);
        }
        else if (event->type() == QEvent::Leave) {
            QFont font = ui->label_ForgetPWD->font();
            font.setUnderline(false);
            ui->label_ForgetPWD->setFont(font);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void IR_LoginWgt::on_pushButton_Register_clicked() {
    emit sigRegister();
}

void IR_LoginWgt::on_pushButton_FingerLogin_clicked() {
    //    IRGLobalStatus* gStatus = Singleton<IRGLobalStatus>::GetInstance();
    //    if (!gStatus->hasFingerprintReader()) {
    //        QMessageBox::critical(this, "错误", "未检测到指纹采集设备", "确定");
    //        return;
    //    }
    //    showMask(true);
    //    m_FingerLogin->show();
}
