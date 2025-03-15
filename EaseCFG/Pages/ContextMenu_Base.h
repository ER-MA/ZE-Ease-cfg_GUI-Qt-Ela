#ifndef CONTEXTMENU_BASE_H
#define CONTEXTMENU_BASE_H

#include "ElaMenu.h"

class ContextMenu_Base : public ElaMenu
{
    Q_OBJECT

public:
    explicit ContextMenu_Base(QWidget* parent = nullptr);
    ~ContextMenu_Base();

    void createNavigateMenu(ElaMenu* parentMenu = nullptr);

Q_SIGNALS:
    Q_SIGNAL void pageProtalNavigation();
    Q_SIGNAL void pagePromotionNavigation();
    Q_SIGNAL void pageServerListNavigation();
    Q_SIGNAL void pageKeyBindNavigation();
    Q_SIGNAL void pageSettingNavigation();

protected:

private:

};

#endif // CONTEXTMENU_BASE_H
