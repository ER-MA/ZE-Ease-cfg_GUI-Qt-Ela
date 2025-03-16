#include "ContextMenu_Base.h"
#include "mainwindow.h"

#include "ElaMenu.h"

#include <QApplication>

ContextMenu_Base::ContextMenu_Base(QWidget* parent) :
    ElaMenu(parent)
{

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

void ContextMenu_Base::createUnversalToolMenu(ElaMenu* parentMenu)
{

}

void ContextMenu_Base::createNavigateMenu(ElaMenu* parentMenu)
{
    // emit getAllPageKeysRequest(); // 请求所有页面的Key值
    // 功能跳转 >
    ElaMenu* navigateOtherPages = parentMenu->addMenu(ElaIconType::ArrowRightToBracket, "功能跳转");
    // 功能跳转 - 社区门户
    QAction* navigateProtal = navigateOtherPages->addElaIconAction(ElaIconType::House, "社区门户");
    connect(navigateProtal, &QAction::triggered, this, [=]() {
        emit navigationRequest(_pageKeys["Pratal_Page"]);
        });
    // 功能跳转 - 推广工具
    QAction* navigatePromotion = navigateOtherPages->addElaIconAction(ElaIconType::GlobePointer, "推广工具");
    connect(navigatePromotion, &QAction::triggered, this, [=]() {
        emit navigationRequest(_pageKeys["Promotion_Page"]);
        });
    // 功能跳转 - 服务器列表
    QAction* navigateServerList = navigateOtherPages->addElaIconAction(ElaIconType::Server, "服务器列表");
    connect(navigateServerList, &QAction::triggered, this, [=]() {
        emit navigationRequest(_pageKeys["ServerList_Page"]);
        });
    // 功能跳转 - 按键绑定
    QAction* navigateKeyBind = navigateOtherPages->addElaIconAction(ElaIconType::Keyboard, "按键绑定");
    connect(navigateKeyBind, &QAction::triggered, this, [=]() {
        emit navigationRequest(_pageKeys["KeyBind_Page"]);
        });
    // 功能跳转 - 软件设置
    QAction* navigateSetting = parentMenu->addElaIconAction(ElaIconType::GearComplex, "软件设置");
    connect(navigateSetting, &QAction::triggered, this, [=]() {
        emit navigationRequest(_pageKeys["Setting_Page"]);
        });
}

void ContextMenu_Base::receiveAllPageKeys(const QMap<QString, QString>& pageKeys)
{
    _pageKeys = pageKeys;
}
