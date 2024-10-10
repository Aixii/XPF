#include "IR_TestOperatorWgt.h"
#include "IRTestMainDataHandler.h"
#include "IR_ImmediateTestWgt.h"
#include "IR_ParamSettingWgt.h"
#include "ui_IR_TestOperatorWgt.h"
#include <QMessageBox>
#include <QSettings>

IR_TestOperatorWgt::IR_TestOperatorWgt(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_TestOperatorWgt) {
    ui->setupUi(this);

    setProperty("opcode", "OperatorWgt");

    m_IR1Setting = new IR_ParamSettingWgt(IR_Test::IR_1, this);
    m_IR2Setting = new IR_ParamSettingWgt(IR_Test::IR_2, this);
    m_IR3Setting = new IR_ParamSettingWgt(IR_Test::IR_3, this);

    m_ImTestWgt1 = new IR_ImmediateTestWgt(IR_Test::IR_1, this);
    m_ImTestWgt2 = new IR_ImmediateTestWgt(IR_Test::IR_2, this);
    m_ImTestWgt3 = new IR_ImmediateTestWgt(IR_Test::IR_3, this);

    ui->verticalLayout_IRParam->addWidget(m_IR1Setting);
    ui->verticalLayout_IRParam->addWidget(m_IR2Setting);
    ui->verticalLayout_IRParam->addWidget(m_IR3Setting);

    ui->verticalLayout_ImmediateTest->addWidget(m_ImTestWgt1);
    ui->verticalLayout_ImmediateTest->addWidget(m_ImTestWgt2);
    ui->verticalLayout_ImmediateTest->addWidget(m_ImTestWgt3);
}

IR_TestOperatorWgt::~IR_TestOperatorWgt() {
    delete ui;
}

void IR_TestOperatorWgt::init() {
    ui->widget_ImmediateTesst->setStyleSheet("background-color: white;");

    {
        QStringList list = { "500V", "1500V", "2000V", "2500V" };
        ui->comboBox_VolGrade->addItems(list);
        ui->comboBox_VolGrade->setCurrentText("2500V");
    }

    {
        QStringList list = { "0~1000MΩ", "1GΩ~10GΩ" };
        ui->comboBox_ResRange->addItems(list);
        ui->comboBox_ResRange->setCurrentText("1GΩ~10GΩ");
    }

    m_IR1Setting->init();
    m_IR2Setting->init();
    m_IR3Setting->init();

    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();

    QObject::connect(handler, &IRTestMainDataHandler::sigInfoResp, this, &IR_TestOperatorWgt::slotInfoResp);

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigLengthOuttime, this, [this](uint8_t irnum) {
    //        if (irnum == IR_Test::IR_ALL) {
    //            QMessageBox::critical(this, "错误", "读取全部杆长度超时", "确认");
    //        }
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigLengthResp, this, &IR_TestOperatorWgt::slotLengthResp);
    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigInfoResp, this, &IR_TestOperatorWgt::slotInfoResp);

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigOpened, this, [this]() {
    //        ui->label_DevStatus->setStatus(CStatusLabel::Normal);
    //        Singleton<IRGLobalStatus>::GetInstance()->setTestSerialStatus(true);
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigOpenFailed, this, [this]() {
    //        ui->label_DevStatus->setStatus(CStatusLabel::Error);
    //        Singleton<IRGLobalStatus>::GetInstance()->setTestSerialStatus(false);
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigClosed, this, [this]() {
    //        ui->label_DevStatus->setStatus(CStatusLabel::Error);
    //        Singleton<IRGLobalStatus>::GetInstance()->setTestSerialStatus(false);
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigZeroSuccessed, this, [this](uint8_t irnum) {
    //        QString content("设置零点成功");
    //        switch (irnum) {
    //        case IR_Test::IR_1:
    //            content.append(", 杆号：1");
    //            break;
    //        case IR_Test::IR_2:
    //            content.append(", 杆号：2");
    //            break;
    //        case IR_Test::IR_3:
    //            content.append(", 杆号：3");
    //            break;
    //        default:
    //            break;
    //        }
    //        QMessageBox::information(this, "成功", "设置零点成功", "确认");
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigZeroFailed, this, [this](uint8_t irnum) {
    //        QString content("设置零点失败");
    //        switch (irnum) {
    //        case IR_Test::IR_1:
    //            content.append(", 杆号：1");
    //            break;
    //        case IR_Test::IR_2:
    //            content.append(", 杆号：2");
    //            break;
    //        case IR_Test::IR_3:
    //            content.append(", 杆号：3");
    //            break;
    //        default:
    //            break;
    //        }
    //        QMessageBox::critical(this, "失败", content, "确认");
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigZeroOuttime, this, [this](uint8_t irnum) {
    //        QString content("设置零点超时");
    //        switch (irnum) {
    //        case IR_Test::IR_1:
    //            content.append(", 杆号：1");
    //            break;
    //        case IR_Test::IR_2:
    //            content.append(", 杆号：2");
    //            break;
    //        case IR_Test::IR_3:
    //            content.append(", 杆号：3");
    //            break;
    //        default:
    //            break;
    //        }
    //        QMessageBox::critical(this, "超时", content, "确认");
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStartSuccessed, this, [this]() {
    //        ui->comboBox_ResRange->setEnabled(false);
    //        ui->comboBox_VolGrade->setEnabled(false);
    //        ui->comboBox_WorkArea->setEnabled(false);
    //        ui->comboBox_WorkSpace->setEnabled(false);
    //    });

    //    QObject::connect(g_pTestSerialPortManager, &IRTestSerialPortManager::sigStopSuccessed, this, [this]() {
    //        ui->comboBox_ResRange->setEnabled(true);
    //        ui->comboBox_VolGrade->setEnabled(true);
    //        ui->comboBox_WorkArea->setEnabled(true);
    //        ui->comboBox_WorkSpace->setEnabled(true);
    //    });

    //    m_ImTestWgt1->setXRange(0, 1000);
    //    m_ImTestWgt2->setXRange(0, 1000);
    //    m_ImTestWgt3->setXRange(0, 1000);

    //    QObject::connect(m_IR1Setting, &IR_ParamSettingWgt::sigDeviceInfoChanged, m_ImTestWgt1, &IR_ImmediateTestWgt::slotDeviceInfo);
    //    QObject::connect(m_IR2Setting, &IR_ParamSettingWgt::sigDeviceInfoChanged, m_ImTestWgt2, &IR_ImmediateTestWgt::slotDeviceInfo);
    //    QObject::connect(m_IR3Setting, &IR_ParamSettingWgt::sigDeviceInfoChanged, m_ImTestWgt3, &IR_ImmediateTestWgt::slotDeviceInfo);

    //    QSettings settings("d.ini", QSettings::IniFormat);
    //    {
    //        settings.beginGroup("VolGrade_Select");
    //        QString str = settings.value("value").toString();
    //        settings.endGroup();
    //        ui->comboBox_VolGrade->setCurrentText(str);
    //    }
    //    {
    //        settings.beginGroup("ResRange_Select");
    //        QString str = settings.value("value").toString();
    //        settings.endGroup();
    //        ui->comboBox_ResRange->setCurrentText(str);
    //    }
    //    {
    //        settings.beginGroup("WorkSpace_Select");
    //        QString str = settings.value("value").toString();
    //        settings.endGroup();
    //        ui->comboBox_WorkSpace->setCurrentText(str);
    //    }
    //    {
    //        settings.beginGroup("WorkArea_Select");
    //        QString str = settings.value("value").toString();
    //        settings.endGroup();
    //        ui->comboBox_WorkArea->setCurrentText(str);
    //    }

    //    TestDataOperator* testOp = Singleton<TestDataOperator>::GetInstance();

    //    QObject::connect(
    //        testOp, &TestDataOperator::sigNewestTestData, this, [this](TestDataInfo info, QString opcode) {
    //            if (opcode == property("opcode").toString()) {
    //                QString str;
    //                QString cdate = QDate::currentDate().toString("yyyyMMdd");
    //                if (info.isVaild()) {
    //                    QString     code = info.code;
    //                    QStringList list = code.split('-');
    //                    if (list.size() > 2) {
    //                        QString dateS = list.at(0);
    //                        QString times = list.at(1);
    //                        if (dateS == cdate) {
    //                            str += dateS;
    //                            str += "-";
    //                            str += QString::number(times.toInt() + 1);
    //                            return;
    //                        }
    //                    }
    //                }

    //                str += cdate;
    //                str += "-1";
    //                ui->label_testcode->setText(str);
    //            }
    //        },
    //        Qt::UniqueConnection);

    //    testOp->slotQueryNewestTestData(property("opcode").toString());
}

void IR_TestOperatorWgt::refreshParams() {
    //    QString workarea  = Singleton<IRTestParams>::GetInstance()->getCurWorkArea();
    //    QString workspace = Singleton<IRTestParams>::GetInstance()->getCurWorkSpace();
    //    QString vol       = ui->comboBox_VolGrade->itemText(Singleton<IRTestParams>::GetInstance()->getCurVolGrade());
    //    QString res       = ui->comboBox_ResRange->itemText(Singleton<IRTestParams>::GetInstance()->getCurResRange());

    //    QSettings settings("d.ini", QSettings::IniFormat);
    //    {
    //        settings.beginGroup("WorkArea");
    //        QStringList list = settings.value("values").toStringList();
    //        settings.endGroup();
    //        ui->comboBox_WorkArea->clear();
    //        for (QString& str : list) {
    //            ui->comboBox_WorkArea->addItem(str);
    //        }

    //        ui->comboBox_WorkArea->setCurrentText(workarea);
    //    }
    //    {
    //        settings.beginGroup("WorkSpace");
    //        QStringList list = settings.value("values").toStringList();
    //        settings.endGroup();
    //        ui->comboBox_WorkSpace->clear();
    //        for (QString& str : list) {
    //            ui->comboBox_WorkSpace->addItem(str);
    //        }

    //        ui->comboBox_WorkSpace->setCurrentText(workspace);
    //    }
    //    {
    //        settings.beginGroup("RES_RANGE");
    //        QStringList list = settings.value("values").toStringList();
    //        settings.endGroup();
    //        ui->comboBox_ResRange->clear();
    //        for (QString& str : list) {
    //            ui->comboBox_ResRange->addItem(str);
    //        }

    //        ui->comboBox_ResRange->setCurrentText(res);
    //    }
    //    {
    //        settings.beginGroup("VOL_GRADE");
    //        QStringList list = settings.value("values").toStringList();
    //        settings.endGroup();
    //        ui->comboBox_VolGrade->clear();
    //        for (QString& str : list) {
    //            ui->comboBox_VolGrade->addItem(str);
    //        }

    //        ui->comboBox_VolGrade->setCurrentText(vol);
    //    }
}

void IR_TestOperatorWgt::refreshResRange() {
    QStringList list = ui->comboBox_ResRange->currentText().split('~');
    if (list.size() < 2) {
        return;
    }

    QString V0 = list.at(0);
    QString V1 = list.at(1);

    if (V0.endsWith("Ω")) {
        V0 = V0.left(V0.size() - QString("Ω").size());
    }

    if (V1.endsWith("Ω")) {
        V1 = V1.left(V1.size() - QString("Ω").size());
    }

    double v_0 = 0.0;
    double v_1 = 0.0;

    {
        int fac = 1;
        if (V0.endsWith('M')) {
            fac = 1000000;
            V0  = V0.left(V0.size() - 1);
        }
        else if (V0.endsWith('G')) {
            fac = 1000000000;
            V0  = V0.left(V0.size() - 1);
        }
        else if (V0.endsWith('K')) {
            fac = 1000;
            V0  = V0.left(V0.size() - 1);
        }
        v_0 = V0.toDouble() * fac;
    }

    QString unit = "Ω";
    {
        int fac = 1;
        if (V1.endsWith('M')) {
            fac  = 1000000;
            V1   = V1.left(V1.size() - 1);
            unit = "MΩ";
        }
        else if (V1.endsWith('G')) {
            fac  = 1000000000;
            V1   = V1.left(V1.size() - 1);
            unit = "GΩ";
        }
        else if (V1.endsWith('K')) {
            fac  = 1000;
            V1   = V1.left(V1.size() - 1);
            unit = "KΩ";
        }
        v_1 = V1.toDouble() * fac;
    }

    if (v_1 <= v_0) {
        return;
    }

    if (unit == "MΩ") {
        v_0 /= 1000000;
        v_1 /= 1000000;
    }
    else if (unit == "GΩ") {
        v_0 /= 1000000000;
        v_1 /= 1000000000;
    }
    else if (unit == "KΩ") {
        v_0 /= 1000;
        v_1 /= 1000;
    }

    m_ImTestWgt1->setUnit(unit);
    m_ImTestWgt2->setUnit(unit);
    m_ImTestWgt3->setUnit(unit);
    m_ImTestWgt1->setYRange(v_0, v_1);
    m_ImTestWgt2->setYRange(v_0, v_1);
    m_ImTestWgt3->setYRange(v_0, v_1);
}

void IR_TestOperatorWgt::slotLengthResp(uint8_t irNum, float length) {
    switch (irNum) {
    case IR_Test::IR_1:
        m_IR1Setting->setIRLength(length);
        break;
    case IR_Test::IR_2:
        m_IR2Setting->setIRLength(length);
        break;
    case IR_Test::IR_3:
        m_IR3Setting->setIRLength(length);
        break;
    default:
        break;
    }
}

void IR_TestOperatorWgt::slotInfoResp(uint8_t irNum, float testPos, uint16_t testV, uint32_t testR, uint16_t testA) {

    QString ircode;
    switch (irNum) {
    case IR_Test::IR_1:
        m_ImTestWgt1->addData(testPos, testV * 0.1, testR * 0.1, testA * 0.1);
        ircode = "1";
        break;
    case IR_Test::IR_2:
        m_ImTestWgt2->addData(testPos, testV * 0.1, testR * 0.1, testA * 0.1);
        ircode = "2";
        break;
    case IR_Test::IR_3:
        m_ImTestWgt3->addData(testPos, testV * 0.1, testR * 0.1, testA * 0.1);
        ircode = "3";
        break;
    default:
        break;
    }

    QString code = ui->label_testcode->text();
    if (code.isEmpty()) {
        return;
    }

    code += QString("-%0").arg(ircode);

    //    QString work_space = ui->comboBox_WorkSpace->currentText();
    //    QString work_area  = ui->comboBox_WorkArea->currentText();

    //    UserInfo user = Singleton<UserOperator>::GetInstance()->getCurrentLoginUser();

    //    TestDataInfo info;

    //    info.code      = code;
    //    info.position  = testPos;
    //    info.workspace = work_space;
    //    info.workarea  = work_area;
    //    info.current   = testA;
    //    info.voltage   = testV;
    //    info.resister  = testR;
    //    info.userinfo  = user;
    //    info.devinfo   = dev;

    //    if (ui->radioButton_Full->isChecked()) {
    //        info.testmode = 1;
    //    }
    //    else {
    //        info.testmode = 2;
    //    }

    //    TestDataOperator* testOp = Singleton<TestDataOperator>::GetInstance();
    //    testOp->slotInsertTestData(info, property("opcode").toString());
}

void IR_TestOperatorWgt::slotDevConnected() {
    ui->label_DevStatus->setStatus(CStatusLabel::Normal);
}

void IR_TestOperatorWgt::slotDevDisconnected() {
    ui->label_DevStatus->setStatus(CStatusLabel::Error);
}

void IR_TestOperatorWgt::on_pushButton_readIRLength_clicked() {
    //    if (!Singleton<IRGLobalStatus>::GetInstance()->testSerialStatus()) {
    //        QMessageBox::critical(this, "错误", "未连接到测试设备， 请检查连接参数！", "确认");
    //        return;
    //    }

    //    g_pTestSerialPortManager->sendLengCMD(IR_Test::IR_ALL);
}

void IR_TestOperatorWgt::on_comboBox_WorkSpace_currentIndexChanged(const QString& arg1) {
    //    Singleton<IRTestParams>::GetInstance()->setCurWorkSapce(arg1);
}

void IR_TestOperatorWgt::on_comboBox_WorkArea_currentIndexChanged(const QString& arg1) {
    //    Singleton<IRTestParams>::GetInstance()->setCurWorkArea(arg1);
}

void IR_TestOperatorWgt::on_radioButton_Full_clicked() {
    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();

    handler->test_mode = IR_Test::MODE_FULL;
}

void IR_TestOperatorWgt::on_radioButton_Section_clicked() {
    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();

    handler->test_mode = IR_Test::MODE_SECTION;
}

void IR_TestOperatorWgt::on_pushButton_Start_clicked() {
    //    if (!Singleton<IRGLobalStatus>::GetInstance()->testSerialStatus()) {
    //        QMessageBox::critical(this, "错误", "未连接到测试设备， 请检查连接参数！", "确认");
    //        return;
    //    }

    //    m_IR1Setting->start();
    //    m_IR2Setting->start();
    //    m_IR3Setting->start();
}

void IR_TestOperatorWgt::on_pushButton_Stop_clicked() {
    //    if (!Singleton<IRGLobalStatus>::GetInstance()->testSerialStatus()) {
    //        QMessageBox::critical(this, "错误", "未连接到测试设备， 请检查连接参数！", "确认");
    //        return;
    //    }
    //    m_IR1Setting->stop();
    //    m_IR2Setting->stop();
    //    m_IR3Setting->stop();
}

void IR_TestOperatorWgt::on_pushButton_setZero_clicked() {
    //    if (!Singleton<IRGLobalStatus>::GetInstance()->testSerialStatus()) {
    //        QMessageBox::critical(this, "错误", "未连接到测试设备， 请检查连接参数！", "确认");
    //        return;
    //    }
    //    g_pTestSerialPortManager->sendZeroCMD(IR_Test::IR_ALL);
}

void IR_TestOperatorWgt::on_comboBox_VolGrade_currentIndexChanged(const QString& arg1) {
    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();

    if (arg1 == "500V") {
        handler->test_voltage = 0;
    }
    else if (arg1 == "1500V") {
        handler->test_voltage = 1;
    }
    else if (arg1 == "2000V") {
        handler->test_voltage = 2;
    } // 默认为 3
    else /*if (arg1 == "2500V")*/ {
        handler->test_voltage = 3;
    }
}

void IR_TestOperatorWgt::on_comboBox_ResRange_currentIndexChanged(const QString& arg1) {

    IRTestMainDataHandler* handler = Singleton<IRTestMainDataHandler>::GetInstance();
    if (arg1 == "0~1000MΩ") {
        handler->test_precision = 0;

    } // 默认为 1
    else /*if (arg1 == "1GΩ~10GΩ")*/ {
        handler->test_precision = 1;
    }

    refreshResRange();
}

void IR_TestOperatorWgt::on_comboBox_VolGrade_activated(const QString& arg1) {
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("VolGrade_Select");
    settings.setValue("value", arg1);
    settings.endGroup();
    settings.sync();
}

void IR_TestOperatorWgt::on_comboBox_ResRange_activated(const QString& arg1) {
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("ResRange_Select");
    settings.setValue("value", arg1);
    settings.endGroup();
    settings.sync();
}

void IR_TestOperatorWgt::on_comboBox_WorkSpace_activated(const QString& arg1) {
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("WorkSpace_Select");
    settings.setValue("value", arg1);
    settings.endGroup();
    settings.sync();
}

void IR_TestOperatorWgt::on_comboBox_WorkArea_activated(const QString& arg1) {
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("WorkArea_Select");
    settings.setValue("value", arg1);
    settings.endGroup();
    settings.sync();
}
