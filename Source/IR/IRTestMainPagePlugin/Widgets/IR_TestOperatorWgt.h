#ifndef IR_TESTOPERATORWGT_H
#define IR_TESTOPERATORWGT_H

#include "IR_ImmediateTestWgt.h"
#include "IR_ParamSettingWgt.h"
#include <QWidget>

namespace Ui {
class IR_TestOperatorWgt;
}

class IR_TestOperatorWgt : public QWidget {
    Q_OBJECT

public:
    explicit IR_TestOperatorWgt(QWidget* parent = nullptr);
    ~IR_TestOperatorWgt();

    void init();

    void refreshParams();
    void refreshResRange();

public slots:
    void slotLengthResp(uint8_t irNum, float length);
    void slotInfoResp(uint8_t irNum, float testPos, uint16_t testV, uint32_t testR, uint16_t testA);
    void slotDevConnected();
    void slotDevDisconnected();

private slots:
    void on_pushButton_readIRLength_clicked();

    void on_pushButton_Start_clicked();

    void on_comboBox_VolGrade_currentIndexChanged(int index);

    void on_comboBox_ResRange_currentIndexChanged(int index);

    void on_comboBox_WorkSpace_currentIndexChanged(const QString& arg1);

    void on_comboBox_WorkArea_currentIndexChanged(const QString& arg1);

    void on_radioButton_Full_clicked();

    void on_radioButton_Section_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_setZero_clicked();

    void on_comboBox_VolGrade_currentIndexChanged(const QString& arg1);
    void on_comboBox_ResRange_currentIndexChanged(const QString& arg1);

    void on_comboBox_VolGrade_activated(const QString& arg1);

    void on_comboBox_ResRange_activated(const QString& arg1);

    void on_comboBox_WorkSpace_activated(const QString& arg1);

    void on_comboBox_WorkArea_activated(const QString& arg1);

private:
    Ui::IR_TestOperatorWgt* ui;
    IR_ParamSettingWgt*     m_IR1Setting;
    IR_ParamSettingWgt*     m_IR2Setting;
    IR_ParamSettingWgt*     m_IR3Setting;
    IR_ImmediateTestWgt*    m_ImTestWgt1;
    IR_ImmediateTestWgt*    m_ImTestWgt2;
    IR_ImmediateTestWgt*    m_ImTestWgt3;
};

#endif // IR_TESTOPERATORWGT_H
