#ifndef XPFPLUGINHELPERIMPL_H
#define XPFPLUGINHELPERIMPL_H

#include <IXPFPluginHelper>
#include <QLinkedList>
#include <QMap>
#include <QVariant>

namespace XPF {
class XPFPluginHelperImplPrivate;
}

class XPFCore;

class XPFPluginHelperImpl
    : public IXPFPluginHelper {
public:
    XPFPluginHelperImpl();
    ~XPFPluginHelperImpl();

    void setXPFScreenWidget(int screenID, QWidget* widget);

    // IXPFPluginHelper interface
public:
    QString getXPFBinDir() override;
    QString getXPFBinConfigDir() override;

    void subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) override;
    void unsubMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) override;
    void sendMessage(const QString& topic, uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr) override;
    void sendSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param = QVariant(), IXPFPlugin* sender = nullptr) override;

    bool registerService(const QString& name, IXPFService* servicePtr) override;

    IXPFService* getService(const QString& name) override;

    QWidget* getXPFScreenWidget(int screenID) override;
    QWidget* getXPFWidgetById(int screenID, const QString& id) override;
    QWidget* getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) override;

    QList<QWidget*> getXPFScreenWidgets() override;

private:
    XPF::XPFPluginHelperImplPrivate* m_Private;
};

#endif // XPFPLUGINHELPERIMPL_H
