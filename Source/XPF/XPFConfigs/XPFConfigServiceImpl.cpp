#include "XPFConfigServiceImpl.h"
#include <QDebug>
#include <QMutexLocker>

XPFConfigServiceImpl::XPFConfigServiceImpl() {
}

XPFConfigServiceImpl::~XPFConfigServiceImpl() {
}

void XPFConfigServiceImpl::registerConfigurator(const QString& name, IXPFConfigurator* configurator) {

    QMutexLocker locker(&m_Mutex);

    if (m_Configuratores.contains(name)) {
        qWarning() << "repeat register configurator. name: " << name << ". will ignore this operator.";
        return;
    }
    else {
        m_Configuratores[name] = configurator;
    }
}

IXPFConfigurator* XPFConfigServiceImpl::getConfigurator(const QString& name) {
    QMutexLocker locker(&m_Mutex);

    if (m_Configuratores.contains(name)) {
        return m_Configuratores.value(name);
    }

    return nullptr;
}
