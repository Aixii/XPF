#include "IR_ParamSettingWgt.h"
#include "IRTestMainDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "ui_IR_ParamSettingWgt.h"
#include <QMessageBox>

extern IXPFPluginHelper* g_pPluginHelper;

using namespace IR_Test;

// extern IRTestSerialPortManager* g_pTestSerialPortManager;

IR_ParamSettingWgt::IR_ParamSettingWgt(IR_Number number, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_ParamSettingWgt)
    , m_Number(number) {
    ui->setupUi(this);

    setProperty("opcode", QString("ParamSettingWgt-%0").arg(number));

    ui->pushButton_refresh->init();
    ui->pushButton_refresh->setStyleSheet("background: transparent;"
                                          "border:none;"
                                          "background-repeat: no-repeat;");

    ui->doubleSpinBox_startPos->hide();
    ui->doubleSpinBox_endPos->hide();
    ui->doubleSpinBox_speed->hide();
    ui->label_startPos->hide();
    ui->label_endPos->hide();
    ui->label_speed->hide();
}

IR_ParamSettingWgt::~IR_ParamSettingWgt() {
    delete ui;
}

void IR_ParamSettingWgt::init() {
    //    auto devOp = Singleton<DeviceOperator>::GetInstance();
    //    QObject::connect(devOp, &DeviceOperator::sigDevice, this, [this](DeviceInfo info, QString opcode) {
    //        if (opcode != property("opcode").toString()) {
    //            return;
    //        }
    //        if (info.code == ui->lineEdit_devcode->text()) {
    //            m_DevInfo = info;
    //            ui->lineEdit_length->setText(QString::number(info.length));
    //            ui->doubleSpinBox_endPos->setValue(info.length);
    //            emit sigDeviceInfoChanged(info);
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigLengthResp, this, [this](uint8_t num, float len) {
    //        if (num == m_Number) {
    //            ui->lineEdit_length->setText(QString::number(len));
    //            ui->doubleSpinBox_endPos->setValue(len);
    //            m_DevInfo.length = len;
    //            emit sigDeviceInfoChanged(m_DevInfo);
    //            ui->pushButton_refresh->stop();
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigLengthOuttime, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            ui->pushButton_refresh->stop();
    //            QMessageBox::critical(this, "错误", QString("获取杆长超时，杆号：%1").arg(num));
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStartSuccessed, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            startSuccessedDo();
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStartFailed, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            QMessageBox::critical(this, "错误", QString("启动采集失败, 杆号：%0").arg(number2Des()), "确认");
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStartOuttime, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            QMessageBox::critical(this, "超时", QString("启动采集超时, 杆号：%0").arg(number2Des()), "确认");
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStopSuccessed, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            stopSuccessedDo();
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStopFailed, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            QMessageBox::critical(this, "错误", QString("停止采集失败, 杆号：%0").arg(number2Des()), "确认");
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStopOuttime, this, [this](uint8_t num) {
    //        if (num == m_Number) {
    //            QMessageBox::critical(this, "超时", QString("停止采集超时, 杆号：%0").arg(number2Des()), "确认");
    //        }
    //    });

    //    QObject::connect(
    //        ui->lineEdit_devcode, &QLineEdit::textEdited, this, [this]() {
    //            ui->lineEdit_devcode->setStyleSheet("border: 1px solid black;");
    //        },
    //        Qt::UniqueConnection);
}

void IR_ParamSettingWgt::setIRLength(float length) {
    ui->lineEdit_length->setText(QString::number(length));
}

void IR_ParamSettingWgt::start() {
    //    if (Singleton<IRGLobalStatus>::GetInstance()->getTestIRStatus(m_Number)) {
    //        return;
    //    }
    //    if (ui->lineEdit_devcode->text().isEmpty()) {
    //        ui->lineEdit_devcode->setStyleSheet("border: 1px solid red;");
    //        return;
    //    }

    //    IRTestParams* params = Singleton<IRTestParams>::GetInstance();

    //    double startPos = ui->doubleSpinBox_startPos->value();
    //    double endPos   = ui->doubleSpinBox_endPos->value();
    //    double speed    = ui->doubleSpinBox_speed->value();

    //    g_pTestSerialPortManager->sendStartCMD(m_Number,
    //                                           (IR_Test::IR_VG)params->getCurVolGrade(),
    //                                           (IR_Test::IR_Precision)params->getCurResRange(),
    //                                           startPos,
    //                                           endPos,
    //                                           speed,
    //                                           params->getTestMode());
}

void IR_ParamSettingWgt::stop() {
    //    if (!Singleton<IRGLobalStatus>::GetInstance()->getTestIRStatus(m_Number)) {
    //        return;
    //    }

    //    g_pTestSerialPortManager->sendStopCMD(m_Number);
}

void IR_ParamSettingWgt::startSuccessedDo() {
    //    ui->label_WorkStatusDes->setText("正在采集");
    //    ui->label_WorkStatus->setStatus(CStatusLabel::Normal);
    //    Singleton<IRGLobalStatus>::GetInstance()->setTestIRStatus(m_Number, true);
}

void IR_ParamSettingWgt::stopSuccessedDo() {
    //    ui->label_WorkStatusDes->setText("停止采集");
    //    ui->label_WorkStatus->setStatus(CStatusLabel::Error);
    //    Singleton<IRGLobalStatus>::GetInstance()->setTestIRStatus(m_Number, false);
}

QString IR_ParamSettingWgt::number2Des() {
    QString des = "未知";
    switch (m_Number) {
    case IR_1:
        des = "1";
        break;
    case IR_2:
        des = "2";
        break;
    case IR_3:
        des = "3";
        break;
    default:
        break;
    }
    return des;
}

bool IR_ParamSettingWgt::checkDevStatus() {
    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();
    if (!handler->dev_status) {
        QMessageBox::critical(this, u8"错误", u8"未连接到测试设备， 请在【设置】中检查连接参数！", u8"确认");
        return false;
    }
    return true;
}

void IR_ParamSettingWgt::on_pushButton_refresh_clicked() {
    //    if (!checkDevStatus()) {
    //        return;
    //    }
    //    g_pTestSerialPortManager->sendLengCMD(m_Number);
    //    ui->pushButton_refresh->start();
}

void IR_ParamSettingWgt::on_pushButton_start_clicked() {
    if (!checkDevStatus()) {
        return;
    }

    if (ui->lineEdit_devcode->text().isEmpty()) {
        ui->lineEdit_devcode->setStyleSheet("border: 1px solid red;");
        return;
    }

    double startPos = ui->doubleSpinBox_startPos->value();
    double endPos   = ui->doubleSpinBox_endPos->value();
    double speed    = ui->doubleSpinBox_speed->value();

    IR::st_Dev_Cmd cmd;
    cmd.cmd   = IR_Test::CMD_STRT;
    cmd.irnum = m_Number;

    // 挡位 精度 起止 速度 模式
    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();

    cmd.arg0 = handler->test_voltage;
    cmd.arg1 = handler->test_precision;
    cmd.arg2 = startPos * 10;
    cmd.arg3 = endPos * 10;
    cmd.arg4 = (uint16_t)speed;
    cmd.arg5 = handler->test_mode;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd));

    memcpy(bytes.data(), &cmd, sizeof(IR::st_Dev_Cmd));
    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_SET_ZERO_ID, bytes);
}

void IR_ParamSettingWgt::on_pushButton_stop_clicked() {
    if (!checkDevStatus()) {
        return;
    }

    stop();
}

void IR_ParamSettingWgt::on_pushButton_zero_clicked() {
    if (!checkDevStatus()) {
        return;
    }

    IR::st_Dev_Cmd cmd;
    cmd.cmd   = IR_Test::CMD_ZERO;
    cmd.irnum = m_Number;

    QByteArray bytes;
    bytes.resize(sizeof(IR::st_Dev_Cmd));

    memcpy(bytes.data(), &cmd, sizeof(IR::st_Dev_Cmd));
    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_SET_ZERO_ID, bytes);
}

void IR_ParamSettingWgt::on_lineEdit_devcode_editingFinished() {
    //    Singleton<DeviceOperator>::GetInstance()->slotQueryDeviceByCode(ui->lineEdit_devcode->text(), property("opcode").toString());
}
