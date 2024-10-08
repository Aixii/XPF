#include "XPFUiTool.h"
#include "IXPFPluginHelper.h"
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
        QFile        file(fileName);
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
            QMessageBox::warning(nullptr,
                                 QObject::tr(u8"警告"),
                                 QObject::tr(u8"%1格式错误"),
                                 QObject::tr(u8"知道了"));
            break;
        }

        widget = new QWidget();

        QLayout* layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);

        QWidget* w = createUi(mainElement);
        layout->addWidget(w);
    }
    while (0);

    return widget;
}

QWidget* XPFUiTool::createWidget(const QDomElement& em) {
    QWidget* widget      = new QWidget;
    QString  orientation = em.attribute("layout_orientation", "vertical");
    QLayout* layout      = nullptr;
    if (orientation == "horizontal") {
        layout = new QHBoxLayout(widget);
    }
    else {
        layout = new QVBoxLayout(widget);
    }
    widget->setLayout(layout);

    QDomNode node = em.firstChild();
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement cem = node.toElement();
            QWidget*    cw  = createUi(cem);
            layout->addWidget(cw);
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
        int stretch = 0;
        if (index < list.size()) {
            stretch = QString(list.at(index)).toUInt();
        }
        splitter->setStretchFactor(index, stretch);
        index++;
        node = node.nextSibling();
    }
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
        cw->setParent(widget);

        widget->addWidget(cw);
        cem = cem.nextSiblingElement();
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
    else {
        return nullptr;
    }

    if (widget != nullptr) {
        QString id = em.attribute("id");
        widget->setObjectName(id);
    }

    return widget;
}
