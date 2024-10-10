#ifndef IRTOPICDEF_H
#define IRTOPICDEF_H

#include <QByteArray>
#include <Qt>
#include <strings.h>
#include <vector>

static char TOPIC_IRAccount[] = "TOPIC_IRAccount";
static char TOPIC_IRTest[]    = "TOPIC_IRTest";

namespace IR {
enum MSG_ID {
    LOGIN_REQUEST_ID   = 0x00001000,
    LOGIN_RESULT_ID    = 0x00001001,
    LOGIN_SUCCEED_ID   = 0x00001002,
    LOGIN_USER_INFO_ID = 0x00001003,
    LOGOUT_MSG_ID      = 0x00001010,

    //    USER_INFO_QUERY_ID = 0x00001100,
    //    USER_INFO_MODIFY_ID = 0x00001101,

    DEV_SET_PORT_ID   = 0x00002000, // 参数字符串
    DEV_SET_ZERO_ID   = 0x00002001,
    DEV_GET_LENGTH_ID = 0x00002002,
    DEV_START_ID      = 0x00002003,
    DEV_STOP_ID       = 0x00002004,

    DEV_SET_ZERO_RESP_ID   = 0x00002011,
    DEV_GET_LENGTH_RESP_ID = 0x00002012,
    DEV_START_RESP_ID      = 0x00002013,
    DEV_STOP_RESP_ID       = 0x00002014,
    DEV_TEST_DATA_RESP_ID  = 0x00002015,

    DEV_CONNECTED_NOTIFY_ID    = 0x00002100,
    DEV_DISCONNECTED_NOTIFY_ID = 0x00002101,

};

typedef struct LOGIN_RESULT
{
    bool result;
    char message[128];

    LOGIN_RESULT() {
        result = false;
        memset(message, 0, sizeof(message));
    }

    ~LOGIN_RESULT() {
        Q_UNUSED(TOPIC_IRAccount)
        Q_UNUSED(TOPIC_IRTest)
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

typedef struct USER_INFO
{
    int  id;
    int  grade;
    int  status;
    char username[128];
    char password[128];
    char usercode[128];
    char phone[16];
    int  finger_index;

    short image_size;

    QByteArray finger_image;

    USER_INFO() {
        id           = 0;
        grade        = 0;
        status       = 0;
        finger_index = 0;
        image_size   = 0;
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
        memset(usercode, 0, sizeof(usercode));
        memset(phone, 0, sizeof(phone));
    }

    ~USER_INFO() {
    }

    USER_INFO(const USER_INFO& other) {
        *this = other;
    }

    USER_INFO& operator=(const USER_INFO& other) {
        if (this != &other) {
            this->id           = other.id;
            this->grade        = other.grade;
            this->status       = other.status;
            this->finger_index = other.finger_index;
            this->image_size   = other.image_size;

            memcpy(this->username, other.username, sizeof(this->username));
            memcpy(this->password, other.password, sizeof(this->password));
            memcpy(this->usercode, other.usercode, sizeof(this->usercode));
            memcpy(this->phone, other.phone, sizeof(this->phone));

            this->finger_image = other.finger_image;
        }

        return *this;
    }

    int pack(char* buffer, int size) {
        int offset = sizeof(id) + sizeof(grade) + sizeof(status) + sizeof(finger_index) + sizeof(username) + sizeof(password) + sizeof(usercode) + sizeof(phone) + sizeof(image_size);
        if (size < (offset + image_size)) {
            return 0;
        }
        memcpy(buffer, this, offset);

        memcpy(buffer + offset, finger_image.data(), finger_image.size());

        return offset + image_size;
    }

    int unpack(const char* buffer, int size) {

        int offset = sizeof(id) + sizeof(grade) + sizeof(status) + sizeof(finger_index) + sizeof(username) + sizeof(password) + sizeof(usercode) + sizeof(phone) + sizeof(image_size);
        if (size < offset) {
            return 0;
        }
        memcpy(this, buffer, offset);

        if (size < (this->image_size + offset)) {
            return 0;
        }

        this->finger_image.append(buffer + offset, this->image_size);

        return offset + this->image_size;
    }

    int size() {
        int offset = sizeof(id) + sizeof(grade) + sizeof(status) + sizeof(finger_index) + sizeof(username) + sizeof(password) + sizeof(usercode) + sizeof(phone) + sizeof(image_size);
        return offset + image_size;
    }
} st_UserInfo;

typedef struct DEV_CMD
{
    uint8_t  cmd;
    uint8_t  irnum;
    uint32_t arg0;
    uint32_t arg1;
    uint32_t arg2;
    uint32_t arg3;
    uint32_t arg4;
    uint32_t arg5;

    DEV_CMD() {
        memset(this, 0, sizeof(*this));
    }
} st_Dev_Cmd;

typedef st_Dev_Cmd st_Dev_Cmd_Resp;

}

#endif // IRTOPICDEF_H
