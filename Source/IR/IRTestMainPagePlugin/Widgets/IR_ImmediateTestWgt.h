#ifndef IR_IMMEDIATETESTWGT_H
#define IR_IMMEDIATETESTWGT_H

//#include "DeviceOperator.h"
#include "IRTestParamDefine.h"
#include "qcatenaryplot.h"
#include <QWidget>

namespace Ui {
class IR_ImmediateTestWgt;
}

class IR_ImmediateTestWgt : public QWidget {
    Q_OBJECT

public:
    explicit IR_ImmediateTestWgt(IR_Test::IR_Number number, QWidget* parent = nullptr);
    ~IR_ImmediateTestWgt();

    void setXRange(double, double);
    void setYRange(double, double);

    void setUnit(const QString& unit);

    void addData(double testPos, double testV, double testR, double testA);

public slots:
    //    void slotDeviceInfo(DeviceInfo info);

private:
    Ui::IR_ImmediateTestWgt* ui;
    IR_Test::IR_Number       m_IRNumber;
    QPair<double, double>    m_XRange;
    QPair<double, double>    m_YRange;
    QCatenaryPlot*           m_Plot;
};

#endif // IR_IMMEDIATETESTWGT_H
