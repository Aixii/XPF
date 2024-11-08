#include "XPFCore.h"
#include "CrashException.h"
#include <XPFGlobal>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <Windows.h>
#include <codecvt>
#include <iostream>
#include <locale>

static void debugHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    QString stype;
    switch (type) {
    case QtDebugMsg:
        stype = QString("Debug");
        break;
    case QtWarningMsg:
        stype = QString("Warning");
        break;
    case QtCriticalMsg:
        stype = QString("Critical");
        break;
    case QtFatalMsg:
        stype = QString("Fatal");
        break;
    case QtInfoMsg:
        stype = QString("Info");
        break;
    }

    QFile file("log.txt");

    if(file.open(QIODevice::Append))
    {
        file.write(QString("[%0]: %1\n").arg(stype).arg(msg).toUtf8());
        file.close();
    }
}

int main(int argc, char* argv[]) {

    SetUnhandledExceptionFilter(ExceptionFilter);

    QApplication app(argc, argv);
    qInstallMessageHandler(debugHandler);

    XPFCore* core = new XPFCore;

    core->initialize();

    QObject::connect(core, &XPFCore::sigQuitApp, &app, &QApplication::quit);

    // 加载完成之后显示界面
    core->showScreens();

    // 进入事件循环
    int ret = app.exec();

    delete core;
    core = nullptr;
    return ret;
}
