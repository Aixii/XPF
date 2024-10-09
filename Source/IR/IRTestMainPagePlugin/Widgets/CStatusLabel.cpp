#include "CStatusLabel.h"
#include <QPainter>

CStatusLabel::CStatusLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f) {
    m_status = Error;
}

CStatusLabel::CStatusLabel(const QString& text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f) {
    m_status = Error;
}

CStatusLabel::~CStatusLabel() {
}

void CStatusLabel::setStatus(CStatusLabel::Status status) {
    m_status = status;
    update();
}

int CStatusLabel::status() {
    return m_status;
}

void CStatusLabel::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event);

    // 使用 QPainter 绘制指示灯
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔和颜色
    QColor color;
    if (m_status == Normal) {
        color = Qt::green;
    }
    else {
        color = Qt::red;
    }

    painter.setBrush(QBrush(color));
    painter.setPen(Qt::NoPen);

    int min = qMin(width(), height());

    // 绘制圆形指示灯
    double radius = min / 2.0; // 指示灯半径

    double x = (width() - radius) / 2.0; // 水平方向居中
    double y = (height() - radius) / 2.0; // 垂直方向居中
    painter.drawEllipse(x, y, radius, radius);
}
