﻿#include "XPFPluginHelperImpl.h"
#include "Private/XPFPluginHelperImplPrivate.h"
#include <QFileInfo>
#include <QThread>

XPFPluginHelperImpl::XPFPluginHelperImpl()
    : IXPFPluginHelper()
    , m_Private(new XPF::XPFPluginHelperImplPrivate) {
}

XPFPluginHelperImpl::~XPFPluginHelperImpl() {
    if (m_Private != nullptr) {
        delete m_Private;
        m_Private = nullptr;
    }
}

void XPFPluginHelperImpl::setXPFScreenWidget(int screenID, QWidget* widget) {
    m_Private->m_ScreenWidgets[screenID] = widget;
}

QString XPFPluginHelperImpl::getXPFBinDir() {
    return m_Private->getXPFBinDir();
}

QString XPFPluginHelperImpl::getXPFBinConfigDir() {
    return m_Private->getXPFBinConfigDir();
}

void XPFPluginHelperImpl::subMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    m_Private->subMessage(plugin, topic, msgid);
}

void XPFPluginHelperImpl::unsubMessage(IXPFPlugin* plugin, const QString& topic, uint32_t msgid) {
    m_Private->unsubMessage(plugin, topic, msgid);
}

void XPFPluginHelperImpl::sendMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    m_Private->sendMessage(topic, msgid, param, sender);
}

void XPFPluginHelperImpl::sendSyncMessage(const QString& topic, uint32_t msgid, const QVariant& param, IXPFPlugin* sender) {
    m_Private->sendSyncMessage(topic, msgid, param, sender);
}

bool XPFPluginHelperImpl::registerService(const QString& name, IXPFService* servicePtr) {
    return m_Private->registerService(name, servicePtr);
}

IXPFService* XPFPluginHelperImpl::getService(const QString& name) {
    return m_Private->getService(name);
}

QWidget* XPFPluginHelperImpl::getXPFScreenWidget(int screenID) {
    return m_Private->getXPFScreenWidget(screenID);
}

QWidget* XPFPluginHelperImpl::getXPFWidgetById(int screenID, const QString& id) {
    return m_Private->getXPFWidgetById(screenID, id);
}

QWidget* XPFPluginHelperImpl::getXPFWidgetByPlugin(const QString& plugin_name, const QString& plugin_winid) {
    return m_Private->getXPFWidgetByPlugin(plugin_name, plugin_winid);
}

QList<QWidget*> XPFPluginHelperImpl::getXPFScreenWidgets() {
    return m_Private->getXPFScreenWidgets();
}
