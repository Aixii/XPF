#ifndef IR_PARAMSETTINGWGT_H
#define IR_PARAMSETTINGWGT_H

#include "IRTestParamDefine.h"
#include <QWidget>

namespace Ui {
class IR_ParamSettingWgt;
}

class IR_ParamSettingWgt : public QWidget {
    Q_OBJECT
public:
    explicit IR_ParamSettingWgt(IR_Test::IR_Number number, QWidget* parent = nullptr);
    ~IR_ParamSettingWgt();

    void init();

    void setIRLength(float length);

    void start();
    void stop();

private:
    void startSuccessedDo();
    void stopSuccessedDo();

    QString number2Des();

    bool checkDevStatus();

private slots:
    void on_pushButton_refresh_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_zero_clicked();

    void on_lineEdit_devcode_editingFinished();

private:
    Ui::IR_ParamSettingWgt* ui;
    IR_Test::IR_Number      m_Number;
    //    DeviceInfo              m_DevInfo;
};

#endif // IR_PARAMSETTINGWGT_H
