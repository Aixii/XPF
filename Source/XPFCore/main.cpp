#include "XPFCore.h"
#include "XPFGlobal.h"
#include <QApplication>
#include <QString>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    XPFCore *core = new XPFCore;

    if(!core->load())
    {
        QMessageBox::critical(nullptr, QObject::tr(u8"错误"), XPF::xpf_err_msg, QMessageBox::Close);
        delete core;
        core = nullptr;
        return -1;
    }

    // 进入事件循环
    app.exec();

    delete core;
    core = nullptr;
    return 0;
}
