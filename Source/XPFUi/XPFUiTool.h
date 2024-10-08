#ifndef XPFUITOOL_H
#define XPFUITOOL_H

#include <QDomElement>
#include <QtWidgets>

class XPFUiTool {
private:
    XPFUiTool();
    virtual ~XPFUiTool();

public:
    static QWidget* generateWidget(const QString& fileName);

private:
    static QWidget*        createWidget(const QDomElement& em);
    static QTabWidget*     createTabWidget(const QDomElement& em);
    static QSplitter*      createSplitterWidget(const QDomElement& em);
    static QWidget*        createPluginWidget(const QDomElement& em);
    static QStackedWidget* createStackWidget(const QDomElement& em);
    static QWidget*        createUi(const QDomElement& em);
};

#endif // XPFUITOOL_H
