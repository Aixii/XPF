#ifndef IR_TESTMAIN_H
#define IR_TESTMAIN_H

// #include "IR_EditUserDialog.h"
// #include "IR_SettingDialog.h"
#include <QAction>
#include <QMenu>
#include <QWidget>

namespace Ui {
class IR_TestMain;
}

class IR_TestMain : public QWidget {
    Q_OBJECT

public:
    explicit IR_TestMain(QWidget* parent = nullptr);
    ~IR_TestMain();

    void init();

signals:
    void sigLogout();

public slots:
    void slotLoginSuccessed();

private slots:
    void on_pushButton_Logout_clicked();

    void on_toolButton_Menu_clicked();

    void on_toolButton_Setting_clicked();

    void on_toolButton_UserIcon_clicked();

private:
    Ui::IR_TestMain* ui;
    //    IR_SettingDialog*  m_SettingDialog;
    //    IR_EditUserDialog* m_EditUserDialog;

    QMenu* m_menu;

    // 添加选项到菜单
    QAction* m_action_main;
    QAction* m_action_brower;
    QAction* m_action_dm;
};

#endif // IR_TESTMAIN_H
