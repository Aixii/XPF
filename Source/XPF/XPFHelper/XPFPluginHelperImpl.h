#ifndef XPFPLUGINHELPERIMPL_H
#define XPFPLUGINHELPERIMPL_H

#include <IXPFPluginHelper>
#include <QMap>
#include <QVariant>
#include <list>

#ifdef DLL_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif

namespace XPF {
class XPFPluginHelperImplPrivate;
}

class XPFCore;

// 代理-预留处理
class XPFPluginHelperImpl
    : public IXPFPluginHelper {
public:
    XPFPluginHelperImpl();
    ~XPFPluginHelperImpl();

    void setXPFScreenWidget(int screenID, QWidget* widget);

    // IXPFPluginHelper interface
public:
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

    void unregisterService(const QString& name) override;
    bool registerPlugin(IXPFPlugin* plugin, void* who) override;
    void unregisterPlugin(IXPFPlugin* plugin, void* who) override;

private:
    XPF::XPFPluginHelperImplPrivate* m_Private;
};

namespace XPF {
extern "C" DLLAPI IXPFPluginHelper* __stdcall GetXPFPluginHelper();
}

#endif // XPFPLUGINHELPERIMPL_H
