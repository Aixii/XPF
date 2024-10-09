#include "IR_ImmediateTestWgt.h"
#include "ui_IR_ImmediateTestWgt.h"

IR_ImmediateTestWgt::IR_ImmediateTestWgt(IR_Test::IR_Number number, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_ImmediateTestWgt)
    , m_IRNumber(number) {
    ui->setupUi(this);

    m_Plot = new QCatenaryPlot(this);

    ui->gridLayout->addWidget(m_Plot, 1, 0);

    m_XRange.first  = 0;
    m_XRange.second = 1000;

    m_YRange.first  = 0;
    m_YRange.second = 10;

    m_Plot->setRange(m_XRange.first, m_XRange.second, m_YRange.first, m_YRange.second);

    ui->widget_InstrumentPanel->setScaleRange(m_YRange.first, m_YRange.second);
    ui->widget_InstrumentPanel->setScaleValue(m_YRange.first);

    // 添加辅助线
    //    ui->widget_Chart->addAuxiliaryLine(80, QColor(255, 0, 0));
}

IR_ImmediateTestWgt::~IR_ImmediateTestWgt() {
    delete ui;
}

void IR_ImmediateTestWgt::setXRange(double xMin, double xMax) {
    m_XRange.first  = xMin;
    m_XRange.second = xMax;

    ui->gridLayout->removeWidget(m_Plot);
    delete m_Plot;
    m_Plot = new QCatenaryPlot(this);
    ui->gridLayout->addWidget(m_Plot, 1, 0);

    m_Plot->setRange(m_XRange.first, m_XRange.second, m_YRange.first, m_YRange.second);
}

void IR_ImmediateTestWgt::setYRange(double yMin, double yMax) {
    m_YRange.first  = yMin;
    m_YRange.second = yMax;

    ui->gridLayout->removeWidget(m_Plot);
    delete m_Plot;
    m_Plot = new QCatenaryPlot(this);
    ui->gridLayout->addWidget(m_Plot, 1, 0);

    m_Plot->setRange(m_XRange.first, m_XRange.second, yMin, yMax);

    ui->widget_InstrumentPanel->setScaleRange(yMin, yMax);
}

void IR_ImmediateTestWgt::setUnit(const QString& unit) {
    ui->widget_InstrumentPanel->setUnit(unit);
}

void IR_ImmediateTestWgt::addData(double testPos, double testV, double testR, double testA) {
    ui->lineEdit_Vol->setText(QString::number(testV));
    ui->lineEdit_Res->setText(QString::number(testR));
    ui->lineEdit_Cur->setText(QString::number(testA));
    m_Plot->addPoint(m_IRNumber, testPos, testR, QColor(0, 255, 0));
}

//void IR_ImmediateTestWgt::slotDeviceInfo(DeviceInfo info) {
//    ui->lineEdit_code->setText(info.code);
//    ui->lineEdit_spec->setText(info.specification);
//    ui->lineEdit_length->setText(QString::number(info.length));
//}
