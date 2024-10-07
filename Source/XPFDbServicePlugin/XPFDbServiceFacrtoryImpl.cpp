#include "XPFDbServiceFacrtoryImpl.h"

XPFDbServiceFacrtory::XPFDbServiceFacrtory() {
}

XPFDbServiceFacrtory::~XPFDbServiceFacrtory() {
}

std::shared_ptr<XPFDbServiceImpl> XPFDbServiceFacrtory::createXPFDbService() {
    return std::make_shared<XPFDbServiceImpl>("dbService");
}

std::shared_ptr<IXPFDbService *> XPFDbServiceFacrtoryImpl::createXPFDbService(XPFDB::XPFDbDriverType type, const QString &connectName, const XPFDbAttribute &attr)
{

}
