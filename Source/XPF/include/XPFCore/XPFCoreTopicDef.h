#ifndef __XPFDEF_H__
#define __XPFDEF_H__

#include <stdint.h>

static char TOPIC_XPF_CORE[] = "TOPIC_XPF_CORE";

namespace XPFCore_NameSpace {

enum XPF_CORE_MSG_ID : uint32_t {
    MSG_ID_QUIT_APP = 0x00000001,
};


typedef struct NNN
{
    bool n;
    NNN() {
        (void)TOPIC_XPF_CORE;
    }
} NNN;

}
#endif
