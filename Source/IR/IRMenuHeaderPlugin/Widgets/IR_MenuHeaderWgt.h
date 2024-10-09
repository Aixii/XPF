#ifndef IR_MenuHeaderWgt_H
#define IR_MenuHeaderWgt_H

// #include "IR_EditUserDialog.h"
// #include "IR_SettingDialog.h"
#include <QAction>
#include <QMenu>
#include <QWidget>

namespace Ui {
class IR_MenuHeaderWgt;
}

class IR_MenuHeaderWgt : public QWidget {
    Q_OBJECT

public:
    explicit IR_MenuHeaderWgt(QWidget* parent = nullptr);
    ~IR_MenuHeaderWgt();

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
    Ui::IR_MenuHeaderWgt* ui;
    //    IR_SettingDialog*  m_SettingDialog;
    //    IR_EditUserDialog* m_EditUserDialog;

    QMenu* m_menu;

    // 添加选项到菜单
    QAction* m_action_main;
    QAction* m_action_brower;
    QAction* m_action_usermanager;
    QAction* m_action_deviceinfo;
};

#endif // IR_MenuHeaderWgt_H
