#include "IR_SettingDialog.h"
#include "IRSettingDataHandler.h"
#include "IRTopicDef.h"
#include "IXPFPluginHelper.h"
#include "XPFTopicDef.h"
#include "ui_IR_SettingDialog.h"
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSettings>

extern IXPFPluginHelper* g_pPluginHelper;

IR_SettingDialog::IR_SettingDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::IR_SettingDialog) {
    ui->setupUi(this);
}

IR_SettingDialog::~IR_SettingDialog() {
    delete ui;
}

void IR_SettingDialog::init() {

    ui->widget_WorkArea->setTitle("工区列表");
    ui->widget_WorkSpace->setTitle("车间列表");
    ui->widget_VGrade->setTitle("电压等级");
    ui->widget_RRange->setTitle("电阻量程");

    resetInfo();

    ui->pushButton_refresh->init();
    ui->pushButton_refresh->setStyleSheet("background: transparent;"
                                          "border:none;"
                                          "background-repeat: no-repeat;");
}

void IR_SettingDialog::showEvent(QShowEvent* event) {
    resetInfo();
    QDialog::showEvent(event);
}

void IR_SettingDialog::resetInfo() {
    on_pushButton_refresh_clicked();

    QSettings settings("d.ini", QSettings::IniFormat);
    {
        QStringList list = { "500V", "1500V", "2000V", "2500V" };
        ui->widget_VGrade->setValues(list);
    }

    {
        QStringList list = { "0~1000MΩ", "1GΩ~10GΩ" };
        ui->widget_RRange->setValues(list);
    }

    {
        settings.beginGroup("WorkSpace");
        QStringList list = settings.value("values").toStringList();
        settings.endGroup();

        ui->widget_WorkSpace->setValues(list);
    }

    {
        settings.beginGroup("WorkArea");
        QStringList list = settings.value("values").toStringList();
        settings.endGroup();

        ui->widget_WorkArea->setValues(list);
    }
}

void IR_SettingDialog::apply() {
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("TEST_PORT");
    QString port = settings.value("port", "").toString();

    IRSettingDataHandler* handler = Singleton<IRSettingDataHandler>::GetInstance();

    if (handler->dev_status && ui->comboBox->currentText() == port) {
        settings.endGroup();
        return;
    }

    settings.setValue("port", ui->comboBox->currentText());
    g_pPluginHelper->sendMessage(TOPIC_IRTest, IR::DEV_SET_PORT_ID, ui->comboBox->currentText());

    settings.endGroup();
}

void IR_SettingDialog::closeDialog() {
    QVariantMap map;
    map["screenID"] = 0;
    map["widgetID"] = "settingdialog";
    g_pPluginHelper->sendMessage(TOPIC_Ui, XPFUi::HIDE_POPUP_ID, map);
}

void IR_SettingDialog::on_pushButton_apply_clicked() {
    //    QSettings settings("d.ini", QSettings::IniFormat);
    //    {
    //        QStringList list = ui->widget_WorkArea->getValues();
    //        settings.beginGroup("WorkArea");
    //        settings.setValue("values", list);
    //        settings.endGroup();
    //        settings.sync();
    //    }
    //    {
    //        QStringList list = ui->widget_WorkSpace->getValues();
    //        settings.beginGroup("WorkSpace");
    //        settings.setValue("values", list);
    //        settings.endGroup();
    //        settings.sync();
    //    }
    //    {
    //        QStringList list = ui->widget_RRange->getValues();
    //        settings.beginGroup("RES_RANGE");
    //        settings.setValue("values", list);
    //        settings.endGroup();
    //        settings.sync();
    //    }
    //    {
    //        QStringList list = ui->widget_VGrade->getValues();
    //        settings.beginGroup("VOL_GRADE");
    //        settings.setValue("values", list);
    //        settings.endGroup();
    //        settings.sync();
    //    }
    apply();
}

void IR_SettingDialog::on_pushButton_ok_clicked() {
    apply();
    closeDialog();
}

void IR_SettingDialog::on_pushButton_cancle_clicked() {
    resetInfo();
    closeDialog();
}

void IR_SettingDialog::on_pushButton_refresh_clicked() {
    ui->pushButton_refresh->start();

    QTimer::singleShot(1000, this, [this]() {
        ui->pushButton_refresh->stop();
    });

    auto list = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();

    for (QSerialPortInfo& info : list) {
        ui->comboBox->addItem(info.portName());
    }

    // 读配置文件，设置端口信息
    QSettings settings("d.ini", QSettings::IniFormat);
    settings.beginGroup("TEST_PORT");
    QString port = settings.value("port", "").toString();
    settings.endGroup();

    ui->comboBox->setCurrentText(port);
}
