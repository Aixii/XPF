#include "TrayIconRClickWgt.h"
#include <IXPFPluginHelper>
#include <XPFCoreTopicDef>
#include "ui_TrayIconRClickWgt.h"
#include <QEvent>
#include <QFocusEvent>
#include <QLabel>
#include <QMouseEvent>

extern IXPFPluginHelper* g_pPluginHelper;

TrayIconRClickWgt::TrayIconRClickWgt(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TrayIconRClickWgt) {
    ui->setupUi(this);

    this->setFixedHeight(this->maximumHeight());

    QList<QWidget*> screens = g_pPluginHelper->getXPFScreenWidgets();

    QString sheet = "QLabel {"
                    "    background: transparent;"
                    "}"
                    "QLabel:hover {"
                    "    background-color: #add8e6;"
                    "}";

    for (QWidget* widget : screens) {
        int id = widget->property("ID").toInt();

        QLabel* label = new QLabel(widget->objectName(), this);
        label->setAlignment(Qt::AlignCenter);
        label->setProperty("ID", id);

        label->setStyleSheet(sheet);
        label->setObjectName(QString::asprintf("screen_%d", id));
        label->installEventFilter(this);
        ui->verticalLayout->addWidget(label);
    }

    {
        QLabel* label = new QLabel(tr(u8"Quit"), this);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(sheet);
        label->setObjectName("quit");
        label->installEventFilter(this);
        ui->verticalLayout->addWidget(label);
    }
    int w = width();

    this->adjustSize();
    this->setFixedWidth(w);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

TrayIconRClickWgt::~TrayIconRClickWgt() {
    delete ui;
}

void TrayIconRClickWgt::focusOutEvent(QFocusEvent* event) {
    QWidget::focusOutEvent(event);
    // 获取鼠标的全局位置
    QPoint globalPos = QCursor::pos();
    // 获取当前窗口的几何区域
    QRect windowRect = this->geometry();
    // 检查鼠标是否在窗口内
    if (!windowRect.contains(globalPos)) {
        this->close();
    }
}

bool TrayIconRClickWgt::eventFilter(QObject* watched, QEvent* event) {
    if (watched->isWidgetType() && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QLabel* label = qobject_cast<QLabel*>(watched);
            if (label) {
                QRegExp reg("^(screen_)\\d+");
                if (label->objectName() == "quit") {
                    g_pPluginHelper->sendSyncMessage(TOPIC_XPF_CORE, XPFCore_NameSpace::MSG_ID_QUIT_APP);
                }
                else if (reg.exactMatch(label->objectName())) {
                    int id = label->property("ID").toInt();

                    QWidget* widget = g_pPluginHelper->getXPFScreenWidget(id);
                    if (widget != nullptr) {
                        widget->activateWindow();
                        widget->show();
                    }
                    this->close();
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
