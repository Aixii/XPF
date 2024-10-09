#include "IR_InstrumentPanel.h"
#include "IRMathTool.h"
#include <QColor>
#include <math.h>

IR_InstrumentPanel::IR_InstrumentPanel(QWidget* parent)
    : QWidget(parent)
    , m_moveH(0)
    , m_panelRadiuPix(100)
    , m_scaleInv(5.0)
    , m_blankPix(m_panelRadiuPix / 2.5)
    , m_txScaleInv(10.0) {
    m_Unit = "Ω";
    setScaleRange(0, 100.0, 5);
    setThreshold(90.0, false);
    setScaleValue(0.0);
}

IR_InstrumentPanel::~IR_InstrumentPanel() {
}

void IR_InstrumentPanel::setScaleRange(const double& minVal, const double& maxVal, const int seg) {
    if (seg < 2)
        return;
    m_minVal   = minVal;
    m_maxVal   = maxVal;
    double inv = (m_maxVal - m_minVal) / (seg - 1);
    m_txScaleList.clear();
    for (int n = 0; n <= seg; ++n) {
        m_txScaleList.append(QString("%1").arg(m_minVal + inv * n));
    }
    m_txScaleInv = PANEL_COVER_DEG / (seg - 1);
    m_scaleInv   = m_txScaleInv / (int)(m_txScaleInv / 5.0 + 0.5);
    update();
}

void IR_InstrumentPanel::setScaleValue(const double& val) {
    m_currentVal = val;
    m_currentVal = std::min(m_currentVal, m_maxVal);
    m_currentVal = std::max(m_currentVal, m_minVal);

    m_currentDeg = (m_currentVal - m_minVal) / (m_maxVal - m_minVal) * PANEL_COVER_DEG;
    update();
}

void IR_InstrumentPanel::setThreshold(const double& val, bool isLower /*= true*/) {
    m_threshold = val;
    m_threshold = std::min(m_threshold, m_maxVal);
    m_threshold = std::max(m_threshold, m_minVal);
    m_isLow     = isLower;
    update();
}

void IR_InstrumentPanel::setUnit(const QString& unit) {
    m_Unit = unit;
    update();
}

void IR_InstrumentPanel::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    // 平移位置
    painter.translate(this->width() / 2, m_moveH);
    // 抗锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Qt4CompatiblePainting);

    // 绘制扇面（超限显示）
    if ((m_isLow && (m_currentVal < m_threshold)) || (!m_isLow && (m_currentVal > m_threshold))) {
        QPen pen;
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.setBrush(QColor(255, 32, 0, 96));
        painter.drawPie(-m_panelRadiuPix, -m_panelRadiuPix, m_panelRadiuPix * 2, m_panelRadiuPix * 2,
                        PANEL_ROTATE_DEG * 16, PANEL_COVER_DEG * 16);
        painter.setBrush(Qt::white);
        painter.drawPie(-m_blankPix, -m_blankPix, m_blankPix * 2, m_blankPix * 2,
                        PANEL_ROTATE_DEG * 16, PANEL_COVER_DEG * 16);
    }

    // 绘制刻度
    drawScale(painter);

    // 绘制弧线
    drawArc(painter);

    // 绘制文本(当前值)
    QPen pen;
    //    if (m_isLow && (m_currentVal < m_threshold))
    //        pen.setColor(Qt::red);
    //    else if (!m_isLow && (m_currentVal > m_threshold))
    //        pen.setColor(Qt::red);
    //    else
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setBold(true);
    font.setPointSizeF(16);
    painter.setFont(font);
    painter.drawText(QRect(-55, -20, 110, 24), Qt::AlignCenter, QString::number(m_currentVal, 'f', 1));

    // 绘制单位
    font.setPointSizeF(12);
    painter.setFont(font);
    painter.drawText(QRect(-55, -45, 110, 24), Qt::AlignCenter, QString("单位：%0").arg(m_Unit));

    // 绘制指针
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.rotate(-PANEL_COVER_DEG_HALF + m_currentDeg);
    painter.drawLine(0, -m_blankPix - m_blankPix, 0, -m_blankPix - 2);

    QWidget::paintEvent(event);
    //painter.restore();
}

void IR_InstrumentPanel::resizeEvent(QResizeEvent* event) {
    int w = this->width();
    int h = this->height();
    if (PANEL_COVER_DEG <= 180.0) {
        double w_panel  = (double)w / (2.0 * sin(PANEL_COVER_DEG_HALF * D2R));
        m_panelRadiuPix = std::min(w_panel, (double)h) - PANEL_MARGIN_PIX * 2.0;
        m_blankPix      = m_panelRadiuPix / 2.5;
        m_moveH         = h / 2 + m_panelRadiuPix / 2;
    }
    else {
        double h_panel  = (double)h / (1.0 + sin((PANEL_COVER_DEG_HALF - 90.0) * D2R));
        m_panelRadiuPix = std::min(h_panel, (double)w * 0.5) - PANEL_MARGIN_PIX * 2.0;
        m_blankPix      = m_panelRadiuPix / 2.5;
        m_moveH         = (h - h / h_panel * m_panelRadiuPix) / 2 + m_panelRadiuPix;
    }
    QWidget::resizeEvent(event);
}

void IR_InstrumentPanel::drawScale(QPainter& painter) {
    QPen pen;
    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.rotate(-PANEL_COVER_DEG_HALF);
    for (double iD = -PANEL_COVER_DEG_HALF; iD <= PANEL_COVER_DEG_HALF; iD += m_scaleInv) {
        painter.drawLine(0, -m_panelRadiuPix + 6, 0, -m_panelRadiuPix);
        painter.rotate(m_scaleInv);
    }
    painter.rotate(-m_scaleInv);
    // 绘制刻度文本
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.rotate(-PANEL_COVER_DEG);
    for (double iD = -PANEL_COVER_DEG_HALF, n = 0; iD <= PANEL_COVER_DEG_HALF; iD += m_txScaleInv) {
        painter.drawLine(0, -m_panelRadiuPix + 10, 0, -m_panelRadiuPix);
        painter.drawText(QRect(-30, -m_panelRadiuPix + 10, 60, 16), Qt::AlignCenter, m_txScaleList.at(n++));
        painter.rotate(m_txScaleInv);
    }
    painter.rotate(-m_txScaleInv);
    painter.rotate(-PANEL_COVER_DEG_HALF); // 旋转到方向朝北
}

void IR_InstrumentPanel::drawArc(QPainter& painter) {
    QPen pen;
    // 外弧线 分段
    pen.setWidth(4);
    QRect         rect(-m_panelRadiuPix, -m_panelRadiuPix, m_panelRadiuPix * 2, m_panelRadiuPix * 2);
    QList<QColor> colorList;
    colorList << Qt::green << QColor(255, 128, 0) << Qt::red; // 逆时针
    double alen = PANEL_COVER_DEG * 16 / colorList.size();
    for (int n = 0; n < colorList.size(); ++n) {
        pen.setColor(colorList.at(n));
        painter.setPen(pen);
        painter.drawArc(rect, PANEL_ROTATE_DEG * 16 + alen * n, alen);
    }
    // 内弧线
    pen.setColor(Qt::darkGray);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawArc(-m_blankPix, -m_blankPix, m_blankPix * 2, m_blankPix * 2,
                    PANEL_ROTATE_DEG * 16, PANEL_COVER_DEG * 16);
}
