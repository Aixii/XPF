#ifndef IXPFPLUGINHELPER_H
#define IXPFPLUGINHELPER_H

#include "IXPFPlugin.h"
#include "IXPFService.h"
#include <QString>
#include <QVariant>

class IXPFPluginHelper {
public:
    IXPFPluginHelper() {
    }
    virtual ~IXPFPluginHelper() {
    }

    virtual QString getXPFBinDir()       = 0;
    virtual QString getXPFBinConfigDir() = 0;

    virtual void subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid)                                                    = 0;
    virtual void unsubMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid)                                                  = 0;
    virtual void sendMessage(const QString& topic, uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr)     = 0;
    virtual void sendSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr) = 0;

    virtual bool registerService(const QString& name, IXPFService* servicePtr) = 0;

    virtual IXPFService* getService(const QString& name) = 0;

    virtual QWidget* getXPFScreenWidget(int screenID)                                              = 0;
    virtual QWidget* getXPFWidgetById(int screenID, const QString& id)                             = 0;
    virtual QWidget* getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) = 0;

    virtual QList<QWidget*> getXPFScreenWidgets() = 0;
};

#endif // IXPFPLUGINHELPER_H
