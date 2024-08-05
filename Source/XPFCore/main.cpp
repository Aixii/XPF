#include "XPFCore.h"
#include "XPFGlobal.h"
#include <QApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    XPFCore* core = new XPFCore;

    core->initialize();

    // 加载完成之后显示界面
    core->showScreens();

    QObject::connect(core, &XPFCore::sigQuitApp, &app, &QApplication::quit);

    // 进入事件循环
    app.exec();

    delete core;
    core = nullptr;
    return 0;
}
