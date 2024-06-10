#ifndef XPFUIPLUIN_H
#define XPFUIPLUIN_H

#include "IXPFPlugin.h"
#include <QObject>

class XPFUiPluin : public QObject, public IXPFPlugin
{
    Q_OBJECT
    Q_INTERFACES(IXPFPlugin)
    Q_PLUGIN_METADATA(IID IXPFPlugin_IID)
public:
    XPFUiPluin();
};

#endif // XPFUIPLUIN_H
