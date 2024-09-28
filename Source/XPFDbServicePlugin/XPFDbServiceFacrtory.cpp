#include "XPFDbServiceFacrtory.h"

XPFDbServiceFacrtory::XPFDbServiceFacrtory() {
}

XPFDbServiceFacrtory::~XPFDbServiceFacrtory() {
}

std::shared_ptr<XPFDbServiceImpl> XPFDbServiceFacrtory::createXPFDbService() {
    return std::make_shared<XPFDbServiceImpl>("dbService");
}
