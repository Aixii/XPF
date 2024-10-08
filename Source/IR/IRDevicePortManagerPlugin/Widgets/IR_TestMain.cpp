#include "IR_TestMain.h"
// #include "IRTestSerialPortManager.h"
// #include "IR_ImmediateTestWgt.h"
// #include "IR_ParamSettingWgt.h"
// #include "UserOperator.h"
#include "ui_IR_TestMain.h"
#include <QMenu>
#include <QMessageBox>

// extern IRTestSerialPortManager* g_pTestSerialPortManager;

IR_TestMain::IR_TestMain(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_TestMain)
    , m_menu(nullptr)
    , m_action_main(nullptr)
    , m_action_brower(nullptr)
    , m_action_dm(nullptr) {
    ui->setupUi(this);
}

IR_TestMain::~IR_TestMain() {
    delete ui;
}

void IR_TestMain::init() {
    if (m_menu == nullptr) {
        m_menu = new QMenu(ui->toolButton_Menu);
        // 将菜单设置为 QToolButton 的下拉菜单
        ui->toolButton_Menu->setMenu(m_menu);
    }
    // 添加选项到菜单
    if (m_action_main == nullptr) {
        m_action_main = new QAction(QIcon(":/resource/image/more.png"), "主页", m_menu);
        m_menu->addAction(m_action_main);
    }
    if (m_action_brower == nullptr) {
        m_action_brower = new QAction(QIcon(":/resource/image/more.png"), "浏览数据", m_menu);
        m_menu->addAction(m_action_brower);
    }
    if (m_action_dm == nullptr) {
        m_action_dm = new QAction(QIcon(":/resource/image/more.png"), "数据管理", m_menu);
        m_menu->addAction(m_action_dm);
    }

    // 设置按钮为带下拉箭头的按钮
    ui->toolButton_Menu->setPopupMode(QToolButton::MenuButtonPopup);

    QObject::connect(
        m_action_main, &QAction::triggered, this, [this]() {
            ui->stackedWidget->setCurrentWidget(ui->page_Main);
        },
        Qt::UniqueConnection);

    QObject::connect(
        m_action_brower, &QAction::triggered, this, [this]() {
            ui->stackedWidget->setCurrentWidget(ui->page_DataBrower);
        },
        Qt::UniqueConnection);

    QObject::connect(
        m_action_dm, &QAction::triggered, this, [this]() {
            ui->stackedWidget->setCurrentWidget(ui->page_DataManger);
        },
        Qt::UniqueConnection);

    //    QObject::connect(m_SettingDialog, &IR_SettingDialog::sigSettingChanged, this, [this]() {
    //        ui->page_Main->refreshParams();
    //    });

    ui->page_DataManger->init();
    ui->page_DataBrower->init();
    ui->page_Main->init();

    //    m_SettingDialog->init();
    //    m_EditUserDialog->init();

    //    QObject::connect(
    //        m_EditUserDialog, &IR_EditUserDialog::sigModifySucced, this, [this](UserInfo info) {
    //            UserOperator* userOp = Singleton<UserOperator>::GetInstance();
    //            userOp->setCurrentLoginUser(info);

    //            ui->label_UserName->setText(info.username);
    //        },
    //        Qt::UniqueConnection);
}

void IR_TestMain::slotLoginSuccessed() {
    //    UserInfo info = Singleton<UserOperator>::GetInstance()->getCurrentLoginUser();
    //    ui->label_UserName->setText(info.username);

    //    UserOperator* userOp = Singleton<UserOperator>::GetInstance();

    //    switch (userOp->getCurrentLoginUser().grade) {
    //    case 1:
    //        m_menu->addAction(m_action_main);
    //        m_menu->addAction(m_action_brower);
    //        m_menu->addAction(m_action_dm);
    //        ui->stackedWidget->setCurrentWidget(ui->page_Main);
    //        break;
    //    case 2:
    //        m_menu->addAction(m_action_main);
    //        m_menu->addAction(m_action_brower);
    //        m_menu->removeAction(m_action_dm);
    //        ui->stackedWidget->setCurrentWidget(ui->page_Main);
    //        break;
    //    case 3:
    //        m_menu->addAction(m_action_brower);
    //        m_menu->removeAction(m_action_dm);
    //        m_menu->removeAction(m_action_main);
    //        ui->stackedWidget->setCurrentWidget(ui->page_DataBrower);
    //        break;
    //    default:
    //        break;
    //    }
}

void IR_TestMain::on_pushButton_Logout_clicked() {
    emit sigLogout();
}

void IR_TestMain::on_toolButton_Menu_clicked() {
    if (ui->toolButton_Menu->menu()->isVisible()) {
        ui->toolButton_Menu->menu()->hide();
    }
    else {
        ui->toolButton_Menu->showMenu();
    }
}

void IR_TestMain::on_toolButton_Setting_clicked() {
    //    m_SettingDialog->show();
}

void IR_TestMain::on_toolButton_UserIcon_clicked() {
    //    UserOperator* userOp = Singleton<UserOperator>::GetInstance();
    //    m_EditUserDialog->setUserInfo(userOp->getCurrentLoginUser());
    //    m_EditUserDialog->show();
}
