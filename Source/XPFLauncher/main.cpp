#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    (void)argc;
    (void)argv;

    // 获取当前的 PATH
    const char* oldPath = std::getenv("PATH");

    // 设置新的 PATH
    std::string newPathR = "..\\Libs";

    char absolutePath[MAX_PATH];
    if (_fullpath(absolutePath, newPathR.c_str(), MAX_PATH) == nullptr) {
        exit(EXIT_FAILURE);
    }

    std::string newPath(absolutePath);

    newPath += (std::string(";") + std::string(oldPath));

    std::string env = std::string("PATH=") + newPath;

    if (_putenv(env.c_str()) != 0) {
        exit(EXIT_FAILURE);
    }

    const char* plugin_path = std::getenv("QT_PLUGIN_PATH");

    {
        std::string path(absolutePath);
        if (plugin_path != nullptr) {
            path += (std::string(";") + std::string(plugin_path));
        }

        std::string env = std::string("QT_PLUGIN_PATH=") + path;

        if (_putenv(env.c_str()) != 0) {
            exit(EXIT_FAILURE);
        }
    }

    // 启动目标程序
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    si.cb          = sizeof(si);
    si.dwFlags     = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW;

    std::string cmd = ".\\XPF.exe";
   
    //int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, cmd.c_str(), -1, NULL, 0);

    //std::wstring wideStr(sizeNeeded, 0);
    //MultiByteToWideChar(CP_UTF8, 0, cmd.c_str(), -1, &wideStr[0], sizeNeeded);

    if (!CreateProcess(nullptr, /*const_cast<wchar_t*>(wideStr.c_str())*/const_cast<char*>(cmd.c_str()),
                       nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        MessageBox(nullptr, TEXT("Failed to start process"), TEXT("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // 等待目标程序退出
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#endif
    return 0;
}
