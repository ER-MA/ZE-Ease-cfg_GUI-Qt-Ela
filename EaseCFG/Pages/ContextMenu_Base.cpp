#include "ContextMenu_Base.h"

#include "ElaMenu.h"

ContextMenu_Base::ContextMenu_Base(QWidget* parent) :
    ElaMenu(parent)
{
}

ContextMenu_Base::~ContextMenu_Base()
{
}

void ContextMenu_Base::createNavigateMenu(ElaMenu* parentMenu)
{
    // 功能跳转 >
    ElaMenu* navigateOtherPages = parentMenu->addMenu(ElaIconType::ArrowRightToBracket, "功能跳转");
    // 功能跳转 - 社区门户
    QAction* navigateProtal = navigateOtherPages->addElaIconAction(ElaIconType::House, "社区门户");
    connect(navigateProtal, &QAction::triggered, this, [=]() {
        Q_EMIT pageProtalNavigation();
        });
    // 功能跳转 - 推广工具
    QAction* navigatePromotion = navigateOtherPages->addElaIconAction(ElaIconType::GlobePointer, "推广工具");
    connect(navigatePromotion, &QAction::triggered, this, [=]() {
        Q_EMIT pagePromotionNavigation();
        });
    // 功能跳转 - 服务器列表
    QAction* navigateServerList = navigateOtherPages->addElaIconAction(ElaIconType::Server, "服务器列表");
    connect(navigateServerList, &QAction::triggered, this, [=]() {
        Q_EMIT pageServerListNavigation();
        });
    // 功能跳转 - 按键绑定
    QAction* navigateKeyBind = navigateOtherPages->addElaIconAction(ElaIconType::Keyboard, "按键绑定");
    connect(navigateKeyBind, &QAction::triggered, this, [=]() {
        Q_EMIT pageKeyBindNavigation();
        });
    // 功能跳转 - 软件设置
    QAction* navigateSetting = parentMenu->addElaIconAction(ElaIconType::GearComplex, "软件设置");
    connect(navigateSetting, &QAction::triggered, this, [=]() {
        Q_EMIT pageSettingNavigation();
        });
}
