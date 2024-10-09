#include "CRefreshButton.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QVariant>

QT_USE_NAMESPACE

CRefreshButton::CRefreshButton(QWidget* parent)
    : QPushButton(parent)
    , m_Angle(0) {
    m_Timer = new QTimer(this);
    connect(m_Timer, &QTimer::timeout, this, &CRefreshButton::slotRotate);
}

CRefreshButton::~CRefreshButton() {
}

void CRefreshButton::init() {
    m_pixmap = QPixmap(":/image/Resource/refresh.png");
}

void CRefreshButton::start() {
    m_Timer->start(100);
}

void CRefreshButton::stop() {
    m_Timer->stop();
    m_Angle = 0;
    update();
}

void CRefreshButton::paintEvent(QPaintEvent* event) {

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(width() / 2, height() / 2); // 将原点移动到按钮中心
    painter.rotate(m_Angle); // 旋转角度
    painter.translate(-width() / 2, -height() / 2); // 旋转后再把原点移回来

    int   imgSize = qMin(width(), height());
    QRect rect((width() - imgSize) / 2, (height() / imgSize) / 2, imgSize, imgSize);
    painter.drawPixmap(rect, m_pixmap);

    QPushButton::paintEvent(event);
}

void CRefreshButton::slotRotate() {
    m_Angle += 10;
    if (m_Angle >= 360) {
        m_Angle = 0;
    }
    repaint();
}
