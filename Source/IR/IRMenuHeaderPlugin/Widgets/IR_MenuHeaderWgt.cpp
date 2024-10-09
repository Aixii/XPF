#include "IR_MenuHeaderWgt.h"
// #include "IRTestSerialPortManager.h"
// #include "IR_ImmediateTestWgt.h"
// #include "IR_ParamSettingWgt.h"
// #include "UserOperator.h"
#include "IXPFPluginHelper.h"
#include "Service/IR/IAccountManagerService.h"
#include "XPFTopicDef.h"
#include "ui_IR_MenuHeaderWgt.h"
#include <QMenu>
#include <QMessageBox>

extern IXPFPluginHelper* g_pPluginHelper;

// extern IRTestSerialPortManager* g_pTestSerialPortManager;

IR_MenuHeaderWgt::IR_MenuHeaderWgt(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::IR_MenuHeaderWgt)
    , m_menu(nullptr)
    , m_action_main(nullptr)
    , m_action_brower(nullptr)
    , m_action_deviceinfo(nullptr)
    , m_action_usermanager(nullptr) {
    ui->setupUi(this);
}

IR_MenuHeaderWgt::~IR_MenuHeaderWgt() {
    delete ui;
}

void IR_MenuHeaderWgt::init() {
    if (m_menu == nullptr) {
        m_menu = new QMenu(ui->toolButton_Menu);
        // 将菜单设置为 QToolButton 的下拉菜单
        ui->toolButton_Menu->setMenu(m_menu);
    }
    // 添加选项到菜单
    if (m_action_main == nullptr) {
        m_action_main = new QAction(QIcon(":/image/Resource/main.png"), "主页", m_menu);
        m_menu->addAction(m_action_main);
    }

    if (m_action_brower == nullptr) {
        m_action_brower = new QAction(QIcon(":/image/Resource/data.png"), "数据浏览与分析", m_menu);
        m_menu->addAction(m_action_brower);
    }

    if (m_action_deviceinfo == nullptr) {
        m_action_deviceinfo = new QAction(QIcon(":/image/Resource/accessory.png"), "绝缘杆档案", m_menu);
        m_menu->addAction(m_action_deviceinfo);
    }

    if (m_action_usermanager == nullptr) {
        m_action_usermanager = new QAction(QIcon(":/image/Resource/order.png"), "用户管理", m_menu);
        m_menu->addAction(m_action_usermanager);
    }

    // 设置按钮为带下拉箭头的按钮
    ui->toolButton_Menu->setPopupMode(QToolButton::MenuButtonPopup);

    QObject::connect(
        m_action_main, &QAction::triggered, this, [this]() {

        },
        Qt::UniqueConnection);

    QObject::connect(
        m_action_brower, &QAction::triggered, this, [this]() {

        },
        Qt::UniqueConnection);

    QObject::connect(
        m_action_usermanager, &QAction::triggered, this, [this]() {

        },
        Qt::UniqueConnection);

    //    QObject::connect(m_SettingDialog, &IR_SettingDialog::sigSettingChanged, this, [this]() {
    //        ui->page_Main->refreshParams();
    //    });

    //    ui->page_DataManger->init();
    //    ui->page_DataBrower->init();
    //    ui->page_Main->init();

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

void IR_MenuHeaderWgt::slotLoginSuccessed() {

    IAccountManagerService* service = dynamic_cast<IAccountManagerService*>(g_pPluginHelper->getService(IAccountManagerServiceIID));

    IR::st_UserInfo userinfo = service->getCurrentUser();
    ui->label_UserName->setText(userinfo.username);

    switch (userinfo.grade) {
    case 1:
        m_menu->addAction(m_action_main);
        m_menu->addAction(m_action_brower);
        m_menu->addAction(m_action_deviceinfo);
        m_menu->addAction(m_action_usermanager);
        break;
    case 2:
        m_menu->addAction(m_action_main);
        m_menu->addAction(m_action_brower);
        m_menu->removeAction(m_action_usermanager);
        break;
    case 3:
        m_menu->addAction(m_action_brower);
        m_menu->removeAction(m_action_usermanager);
        m_menu->removeAction(m_action_main);
        break;
    default:
        break;
    }
}

void IR_MenuHeaderWgt::on_pushButton_Logout_clicked() {
    emit sigLogout();
}

void IR_MenuHeaderWgt::on_toolButton_Menu_clicked() {
    if (ui->toolButton_Menu->menu()->isVisible()) {
        ui->toolButton_Menu->menu()->hide();
    }
    else {
        ui->toolButton_Menu->showMenu();
    }
}

void IR_MenuHeaderWgt::on_toolButton_Setting_clicked() {
    QVariantMap map;
    map["screenID"] = 0;
    map["widgetID"] = "settingdialog";
    g_pPluginHelper->sendMessage(TOPIC_Ui, XPFUi::SHOW_POPUP_ID, map);
}

void IR_MenuHeaderWgt::on_toolButton_UserIcon_clicked() {
    //    UserOperator* userOp = Singleton<UserOperator>::GetInstance();
    //    m_EditUserDialog->setUserInfo(userOp->getCurrentLoginUser());
    //    m_EditUserDialog->show();
}
