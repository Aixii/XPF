#include "CrashException.h"
#include "XPFCore.h"
#include "XPFGlobal"
#include <QApplication>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

#include <QDateTime>

#include <codecvt>
#include <iostream>
#include <locale>

static QString log_prefix;

static void debugHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
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

    QFile file(QString("log-%0.txt").arg(log_prefix));

    if (file.open(QIODevice::Append | QIODevice::WriteOnly)) {
        file.write(QString("[%0]: %1\n").arg(stype).arg(msg).toUtf8());
        file.close();
    }
    else {
        std::cout << file.errorString().toStdString();
        std::cout << msg.toStdString() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    SetUnhandledExceptionFilter(ExceptionFilter);

    QApplication app(argc, argv);

    QDateTime time = QDateTime::currentDateTime();

    log_prefix = time.toString("yyyyMMdd hh时mm分ss秒");

    qInstallMessageHandler(debugHandler);

    XPFCore* core = new XPFCore;

    int ret = 0;

    do {

        QObject::connect(core, &XPFCore::sigQuitApp, &app, &QApplication::quit);

        if (!core->initialize()) {
            ret = -1;
            break;
        }

        // 加载完成之后显示界面
        core->showScreens();

        // 进入事件循环
        ret = app.exec();
    }
    while (0);

    if (XPF::xpf_err_code != XPF::XPF_ERR_NONE) {
        QMessageBox box(QMessageBox::Critical,
                        QObject::tr(u8"错误"),
                        XPF::xpf_err_msg);
        box.addButton(QObject::tr(u8"确认"), QMessageBox::YesRole);
        box.exec();
    }

    delete core;
    core = nullptr;
    return ret;
}
