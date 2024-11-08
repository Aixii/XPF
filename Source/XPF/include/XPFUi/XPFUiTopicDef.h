#ifndef XPFTOPICDEF_H
#define XPFTOPICDEF_H

static char TOPIC_XPF_UI[] = "TOPIC_XPF_UI";

namespace XPFUi {
enum MSG_ID {
    SHOW_POPUP_ID = 0x00000010, // 参数是id
    HIDE_POPUP_ID = 0x00000020,
};

typedef struct NNN
{
    bool n;
    NNN() {
        (void)TOPIC_XPF_UI;
    }
} NNN;
}

#endif // XPFTOPICDEF_H
