#ifndef XPFCORECONFIGURATOR_H
#define XPFCORECONFIGURATOR_H

#include <IXPFConfigurator>
#include <QObject>

class XPFCoreConfigurator : public QObject
    , public IXPFConfigurator {
    Q_OBJECT
public:
    explicit XPFCoreConfigurator(QObject* parent = nullptr);
    ~XPFCoreConfigurator();

    void init();

    // IXPFConfigurator interface
public:
    QVariant getConfigItem(const QString& config_key) override;
    void     setConfigItem(const QString& config_key, const QVariant& var) override;

private:
    QVariantMap m_Configs;
};

#endif // XPFCORECONFIGURATOR_H
