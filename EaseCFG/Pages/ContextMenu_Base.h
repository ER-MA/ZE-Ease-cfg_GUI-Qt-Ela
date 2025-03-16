#ifndef CONTEXTMENU_BASE_H
#define CONTEXTMENU_BASE_H

#include "ElaMenu.h"

class MainWindow;
class ContextMenu_Base : public ElaMenu
{
    Q_OBJECT

public:
    explicit ContextMenu_Base(QWidget* parent = nullptr);
    ~ContextMenu_Base();

    MainWindow* getMainWindow();

    void createUnversalToolMenu(ElaMenu* parentMenu = nullptr);

    void createNavigateMenu(ElaMenu* parentMenu = nullptr);

signals:
    void navigationRequest(const QString& pageName);
    void getAllPageKeysRequest();
public slots:
    void receiveAllPageKeys(const QMap<QString, QString>& pageKeys);

Q_SIGNALS:
    Q_SIGNAL void pageProtalNavigation();
    Q_SIGNAL void pagePromotionNavigation();
    Q_SIGNAL void pageServerListNavigation();
    Q_SIGNAL void pageKeyBindNavigation();
    Q_SIGNAL void pageSettingNavigation();

protected:

private:
    QMap<QString, QString> _pageKeys;
};

#endif // CONTEXTMENU_BASE_H
