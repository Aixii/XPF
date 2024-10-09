#ifndef XPFTOPICDEF_H
#define XPFTOPICDEF_H

static char TOPIC_Core[]     = "TOPIC_Core";
static char TOPIC_TrayMenu[] = "TOPIC_TrayMenu";
static char TOPIC_Ui[]       = "TOPIC_Ui";

namespace XPFUi {
enum MSG_ID {
    SHOW_POPUP_ID = 0x00000010, // 参数是id
    HIDE_POPUP_ID = 0x00000020,
};
}

#endif // XPFTOPICDEF_H
