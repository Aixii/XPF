#ifndef XPFCORECONFIGURATOR_H
#define XPFCORECONFIGURATOR_H

#include <IXPFConfigurator>
#include <QObject>

class QDomElement;

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
    /**
     * @brief parseScreenXml 解析屏幕相关配置
     * @param em 配置元素
     * @return 配置是否有错误
     */
    bool parseScreenXml(const QDomElement& em);

private:
    QVariantMap m_Configs;
};

#endif // XPFCORECONFIGURATOR_H
