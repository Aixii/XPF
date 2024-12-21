#include "XPFUiTool.h"
#include <IXPFPluginHelper>
#include <QObject>

extern IXPFPluginHelper* g_pPluginHelper;

XPFUiTool::XPFUiTool() {
}

XPFUiTool::~XPFUiTool() {
}

QWidget* XPFUiTool::generateWidget(const QString& fileName) {
    QWidget* widget = nullptr;
    do {
        QDomDocument doc("x");

        QFile file(fileName);

        if (!file.exists()) {
            break;
        }

        if (!file.open(QIODevice::ReadOnly)) {
            break;
        }

        doc.setContent(file.readAll());
        file.close();

        QDomElement root = doc.documentElement();
        if (root.isNull()) {
            break;
        }

        QDomElement mainElement = root.firstChildElement("Widgets");
        if (mainElement.isNull()) {
            // QMessageBox::warning(nullptr,
            //                      QObject::tr(u8"警告"),
            //                      QObject::tr(u8"%1格式错误"),
            //                      QObject::tr(u8"知道了"));
            break;
        }

        widget = new QWidget();

        QLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);

        QWidget* w = createUi(mainElement);
        layout->addWidget(w);

        QDomElement popElement = root.firstChildElement("Popups");
        if (popElement.isNull()) {
            break;
        }

        QDomElement pop = popElement.firstChildElement("Popup");
        while (!pop.isNull()) {
            QWidget* dialog = createUi(pop);
            dialog->setParent(widget);
            dialog->hide();

            dialog->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
            dialog->setStyleSheet("QDialog {background-color: white;}");

            pop = pop.nextSiblingElement("Popup");
        }
    }
    while (0);

    return widget;
}

QWidget* XPFUiTool::createWidget(const QDomElement& em) {
    QWidget* widget = new QWidget;

    QString orientation = em.attribute("layout_orientation", "vertical");

    QString stretches = em.attribute("stretches");

    QStringList stre = stretches.split(",");

    QLayout* layout = nullptr;
    if (orientation == "horizontal") {
        layout = new QHBoxLayout(widget);
    }
    else {
        layout = new QVBoxLayout(widget);
    }

    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    QDomNode node = em.firstChild();

    int index = 0;
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement cem = node.toElement();

            QWidget* cw = createUi(cem);

            if (cw == nullptr) {
                node = node.nextSibling();
                continue;
            }

            layout->addWidget(cw);

            if (orientation == "horizontal") {
                QHBoxLayout* xl = qobject_cast<QHBoxLayout*>(layout);
                xl->setStretch(index, QString(stre.value(index, "0")).trimmed().toInt());
            }
            else {
                QVBoxLayout* xl = qobject_cast<QVBoxLayout*>(layout);
                xl->setStretch(index, QString(stre.value(index, "0")).trimmed().toInt());
            }
            index++;
        }
        node = node.nextSibling();
    }
    return widget;
}

QTabWidget* XPFUiTool::createTabWidget(const QDomElement& em) {
    QTabWidget* tabWidget = new QTabWidget;
    QString     titles    = em.attribute("titles");
    QStringList list      = titles.split(':');
    QDomNode    node      = em.firstChild();
    int         index     = 0;
    while (!node.isNull() && index < list.size()) {
        if (!node.isElement()) {
            node = node.nextSibling();
            continue;
        }
        QDomElement cem = node.toElement();
        QWidget*    cw  = createUi(cem);
        cw->setParent(tabWidget);
        tabWidget->addTab(cw, list.at(index));
        index++;
        node = node.nextSibling();
    }
    return tabWidget;
}

QSplitter* XPFUiTool::createSplitterWidget(const QDomElement& em) {
    QSplitter*  splitter  = new QSplitter;
    QString     stretches = em.attribute("stretch");
    QStringList list      = stretches.split(':');
    QDomNode    node      = em.firstChild();
    int         index     = 0;
    while (!node.isNull()) {
        if (!node.isElement()) {
            node = node.nextSibling();
            continue;
        }
        QDomElement cem = node.toElement();
        QWidget*    cw  = createUi(cem);
        cw->setParent(splitter);

        splitter->addWidget(cw);
        index++;
        node = node.nextSibling();
    }

    QList<int> sizes;
    for (int i = 0; i < list.size() && i < index; i++) {
        int s = list.at(i).toUInt();
        sizes.append(s);
    }

    splitter->setSizes(sizes);
    return splitter;
}

QWidget* XPFUiTool::createPluginWidget(const QDomElement& em) {
    QString pluginName  = em.attribute("plugin_name");
    QString pluginWinID = em.attribute("plugin_winid");
    if (pluginName.isEmpty() || pluginWinID.isEmpty()) {
        return nullptr;
    }
    return g_pPluginHelper->getXPFWidgetByPlugin(pluginName, pluginWinID);
}

QStackedWidget* XPFUiTool::createStackWidget(const QDomElement& em) {
    QStackedWidget* widget = new QStackedWidget;

    QDomElement cem = em.firstChildElement();
    while (!cem.isNull()) {
        QWidget* cw = createUi(cem);

        cem = cem.nextSiblingElement();
        if (cw == nullptr) {
            continue;
        }
        cw->setParent(widget);

        widget->addWidget(cw);
    }

    return widget;
}

QWidget* XPFUiTool::createUi(const QDomElement& em) {
    QWidget* widget  = nullptr;
    QString  tagName = em.tagName();
    if (tagName == "Widget" || tagName == "Widgets") {
        widget = createWidget(em);
    }
    else if (tagName == "TabWidget") {
        widget = createTabWidget(em);
    }
    else if (tagName == "Splitter") {
        widget = createSplitterWidget(em);
    }
    else if (tagName == "PluginWidget") {
        widget = createPluginWidget(em);
    }
    else if (tagName == "StackWidget") {
        widget = createStackWidget(em);
    }
    else if (tagName == "Popup") {
        widget = createDialog(em);
    }
    else {
        return nullptr;
    }

    if (widget != nullptr) {
        QString id = em.attribute("id");
        widget->setObjectName(id);
    }
    else {
        QString id = em.attribute("id");
        QMessageBox::critical(nullptr, u8"错误", QString(u8"创建 UI 控件失败, widget id: %1").arg(id));
    }

    return widget;
}

QDialog* XPFUiTool::createDialog(const QDomElement& em) {
    QDialog* dialog = new QDialog();

    QString title = em.attribute("title");
    dialog->setWindowTitle(title);

    QString size = em.attribute("size");

    if (!size.isEmpty()) {
        QStringList sizes = size.split(":");

        int width  = sizes.value(0, "640").toInt();
        int height = sizes.value(1, "480").toInt();
        dialog->setFixedSize(width, height);
    }

    QString pluginName  = em.attribute("plugin_name");
    QString pluginWinID = em.attribute("plugin_winid");
    if (pluginName.isEmpty() || pluginWinID.isEmpty()) {
        return nullptr;
    }
    QWidget* content = g_pPluginHelper->getXPFWidgetByPlugin(pluginName, pluginWinID);
    if (content == nullptr) {
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Critical, QObject::tr("错误"),
                                              QString(QObject::tr(u8"无法加载UI, pluginName: %0, winID: %1")).arg(pluginName).arg(pluginWinID),
                                              QMessageBox::Ok);

        msgBox->button(QMessageBox::Ok)->setText(QObject::tr(u8"确定"));
        msgBox->exec();
        msgBox->deleteLater();
        return dialog;
    }

    QString modal = em.attribute("modal");
    if (modal == "true") {
        dialog->setModal(true);
    }
    else {
        dialog->setModal(false);
    }

    dialog->setLayout(new QVBoxLayout(dialog));
    dialog->layout()->addWidget(content);
    dialog->setContentsMargins(0, 0, 0, 0);
    dialog->layout()->setContentsMargins(0, 0, 0, 0);

    return dialog;
}
