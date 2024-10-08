#ifndef IRTOPICDEF_H
#define IRTOPICDEF_H

#include <strings.h>

static char TOPIC_IRAccount[] = "TOPIC_IRAccount";

namespace IR {
enum MSG_ID {
    LOGIN_REQUEST_ID = 0x00001000,
    LOGIN_RESULT_ID  = 0x00001001,
};

typedef struct LOGIN_RESULT
{
    bool result;
    char message[128];

    LOGIN_RESULT() {
        result = false;
        memset(message, 0, sizeof(message));
    }

} st_Login_Result;

typedef struct LOGIN_REQUEST
{
    char username[128];
    char password[128];

    LOGIN_REQUEST() {
        memset(this, 0, sizeof(*this));
    }
} st_Login_Request;

}

#endif // IRTOPICDEF_H
