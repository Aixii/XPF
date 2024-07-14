#ifndef XPFPLUGINHELPERIMPL_H
#define XPFPLUGINHELPERIMPL_H

#include "IXPFPluginHelper.h"
#include <QMap>
#include <QLinkedList>
#include <QVariant>

namespace XPF {
class XPFPluginHelperImplPrivate;
}

class XPFCore;

class XPFPluginHelperImpl : public IXPFPluginHelper
{
public:
    XPFPluginHelperImpl();
    ~XPFPluginHelperImpl();

    QList<QWidget*> getScreens();
    void setXPFScreenWidget(int screenID, QWidget *widget);

    // IXPFPluginHelper interface
public:
    QString getXPFBinDir() override;

    QString getXPFBinConfigDir() override;

    void subMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void unsubMessage(IXPFPlugin *plugin, uint32_t msgid) override;
    void sendMessage(uint32_t msgid, const QVariant &param = QVariant(), IXPFPlugin *sender = nullptr) override;
    void sendSyncMessage(uint32_t msgid, const QVariant &param = QVariant(), IXPFPlugin *sender = nullptr) override;
    QWidget *getXPFScreenWidget(int screenID) override;

private:
    XPF::XPFPluginHelperImplPrivate *m_Private;
};


#endif // XPFPLUGINHELPERIMPL_H
