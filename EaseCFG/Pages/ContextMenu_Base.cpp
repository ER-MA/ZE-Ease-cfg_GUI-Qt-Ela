#include "ContextMenu_Base.h"
#include "mainwindow.h"

#include "Protal_Page.h"
#include "Promotion_Page.h"
#include "Page_ServerList.h"
#include "Keybind_Page.h"
#include "T_Setting.h"

#include "ElaMenu.h"
#include "ElaTheme.h"
#include "ElaNavigationRouter.h"

#include <QApplication>

ContextMenu_Base::ContextMenu_Base(QWidget* parent) :
    ElaMenu(parent)
{
    connectionWithMainWindow();
}

ContextMenu_Base::~ContextMenu_Base()
{

}

MainWindow* ContextMenu_Base::getMainWindow() {
    // 获取应用程序的所有顶层窗口
    const QWidgetList topLevelWidgets = QApplication::topLevelWidgets();

    for (QWidget* widget : topLevelWidgets) {
        // 尝试将窗口转换为 MainWindow 类型
        MainWindow* mainWin = qobject_cast<MainWindow*>(widget);
        if (mainWin) {
            return mainWin; // 找到第一个 MainWindow 实例
        }
    }
    return nullptr; // 未找到
}

void ContextMenu_Base::connectionWithMainWindow()
{
    MainWindow* mainWindow = getMainWindow();
    if (!mainWindow) {
        return;
    }
    connect(this, &ContextMenu_Base::navigationRequest, mainWindow, &MainWindow::handleNavigationRequest);
    connect(this, &ContextMenu_Base::getAllPageKeysRequest, mainWindow, &MainWindow::handleGetAllPageKeysRrequest);
    connect(mainWindow, &MainWindow::sendAllPageKeys, this, &ContextMenu_Base::receiveAllPageKeys);
}

void ContextMenu_Base::createTestMenu(ElaMenu* parentMenu)
{
    // 创建测试菜单
    ElaMenu* test1Menu = parentMenu->addMenu(ElaIconType::Bug, "FirstMenu1");
    test1Menu->addAction("SecondAction1");
    test1Menu->addAction("SecondAction2");

    ElaMenu* test13Menu = test1Menu->addMenu(ElaIconType::BanBug, "SecondMenu3");
    test13Menu->addAction("ThirdAction1");
    test13Menu->addAction("ThirdAction2");
    test13Menu->addAction("ThirdAction3");

    ElaMenu* test2Menu = parentMenu->addMenu(ElaIconType::BugSlash, "FirstMenu2");
    test2Menu->addAction("SecondAction1");
    test2Menu->addAction("SecondAction2");
    test2Menu->addAction("SecondAction3");
    test2Menu->addAction("SecondAction4");
}

void ContextMenu_Base::createCommonToolMenu(ElaMenu* parentMenu)
{
    QAction* routeBack = parentMenu->addElaIconAction(ElaIconType::ArrowTurnLeft, "返回", QKeySequence::Back);
    connect(routeBack, &QAction::triggered, this, [=]() {
        ElaNavigationRouter::getInstance()->navigationRouteBack();
    });
}

void ContextMenu_Base::createUnversalToolMenu(ElaMenu* parentMenu)
{
    // 创建通用工具菜单
    MainWindow* mainWindow = getMainWindow();
    if (!mainWindow) {
        return;
    }
    // 软件工具 - 窗口置顶
    QAction* topWindowAction = new QAction("窗口置顶", parentMenu);
    connect(topWindowAction, &QAction::triggered, this, [=]() {
        mainWindow->setIsStayTop(!mainWindow->getIsStayTop());
    });
    parentMenu->addAction(topWindowAction);
    connect(parentMenu, &ElaMenu::menuShow, topWindowAction, [=]() {
        bool isStayTop = mainWindow->getIsStayTop();
        topWindowAction->setProperty("ElaIconType", isStayTop ? QChar((unsigned short)ElaIconType::ArrowDownFromArc) : QChar((unsigned short)ElaIconType::ArrowUpToArc));
        topWindowAction->setText(isStayTop ? "取消置顶" : "置顶窗口");
    });
    // 软件工具 - 主题切换
    QAction* themsSwitchAction = new QAction("主题切换", parentMenu);
    connect(themsSwitchAction, &QAction::triggered, this, [=]() {
        const bool isLight = (eTheme->getThemeMode() == ElaThemeType::Light);
        eTheme->setThemeMode(isLight ? ElaThemeType::Dark : ElaThemeType::Light);
    });
    parentMenu->addAction(themsSwitchAction);
    connect(parentMenu, &ElaMenu::menuShow, themsSwitchAction, [=]() {
        bool isLight = (eTheme->getThemeMode() == ElaThemeType::Light);
        themsSwitchAction->setProperty("ElaIconType", isLight ? QChar((unsigned short)ElaIconType::MoonStars) : QChar((unsigned short)ElaIconType::SunBright));
        themsSwitchAction->setText(isLight ? "夜间主题" : "日间主题");
    });
}

void ContextMenu_Base::createNavigateMenu(ElaMenu* parentMenu)
{
    // 创建功能跳转菜单
    // 功能跳转 >
    ElaMenu* navigateOtherPages = parentMenu->addMenu(ElaIconType::ArrowRightToBracket, "功能跳转");
    // 功能跳转 - 社区门户
    QAction* navigateProtal = navigateOtherPages->addElaIconAction(ElaIconType::House, "社区门户");
    connect(navigateProtal, &QAction::triggered, this, [=]() {
        emit navigationRequest(Protal_Page::pageName());
        });
    // 功能跳转 - 推广工具
    QAction* navigatePromotion = navigateOtherPages->addElaIconAction(ElaIconType::GlobePointer, "推广工具");
    connect(navigatePromotion, &QAction::triggered, this, [=]() {
        emit navigationRequest(Promotion_Page::pageName());
        });
    // 功能跳转 - 服务器列表
    QAction* navigateServerList = navigateOtherPages->addElaIconAction(ElaIconType::Server, "服务器列表");
    connect(navigateServerList, &QAction::triggered, this, [=]() {
        emit navigationRequest(Page_ServerList::pageName());
        });
    // 功能跳转 - 按键绑定
    QAction* navigateKeyBind = navigateOtherPages->addElaIconAction(ElaIconType::Keyboard, "按键绑定");
    connect(navigateKeyBind, &QAction::triggered, this, [=]() {
        emit navigationRequest(Keybind_Page::pageName());
        });
    // 功能跳转 - 软件设置
    QAction* navigateSetting = parentMenu->addElaIconAction(ElaIconType::GearComplex, "软件设置");
    connect(navigateSetting, &QAction::triggered, this, [=]() {
        emit navigationRequest(T_Setting::pageName());
        });
}

void ContextMenu_Base::receiveAllPageKeys(const QMap<QString, QString>& pageKeys)
{
    _pageKeys = pageKeys;
}
