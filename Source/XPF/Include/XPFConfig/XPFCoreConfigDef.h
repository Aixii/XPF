#pragma once

#define CONFIG_XPF_APP_NAME        "AppName"
#define CONFIG_XPF_APP_ID          "AppID"
#define CONFIG_XPF_MULTISTART      "MultiStart"
#define CONFIG_XPF_TRAYICON_ENABLE "TrayIconEnable"
#define CONFIG_XPF_SCREEN_NUMBER   "ScreenNumber"

#define CONFIG_XPF_SCREEN              "Screen"
#define CONFIG_XPF_SCREEN_SIZE         "Size"
#define CONFIG_XPF_SCREEN_ISFULLSCREEN "IsFullScreen"
#define CONFIG_XPF_SCREEN_ID           "ID"
#define CONFIG_XPF_SCREEN_NAME         "Name"
#define CONFIG_XPF_SCREEN_ICON         "Icon"
#define CONFIG_XPF_SCREEN_HEADER       "Header"
#define CONFIG_XPF_SCREEN_BODY         "Body"

#define XPF_CORE_CONFIGURATOR_NAME "CoreConfig"

namespace XPFConfig {
enum XPF_CONFIG_ERR {
    XPF_ERR_CONFIG_FILE_NOEXISTS     = 1,
    XPF_ERR_CONFIG_FILE_OPEN_FAILED  = 2,
    XPF_ERR_CONFIG_FILE_PARSE_FAILED = 3,
    XPF_ERR_CONFIG_NOTAPPNAME        = 4,
};
}
