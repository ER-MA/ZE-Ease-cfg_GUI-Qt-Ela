#ifndef CONTEXTMENU_BASE_H
#define CONTEXTMENU_BASE_H

#include "ElaMenu.h"

class MainWindow;
class ContextMenu_Base : public ElaMenu
{
    Q_OBJECT

public:
    explicit ContextMenu_Base(QWidget* parent);
    ~ContextMenu_Base();

    MainWindow* getMainWindow();

    void createTestMenu(ElaMenu* parentMenu);
    void createCommonToolMenu(ElaMenu* parentMenu);
    void createUnversalToolMenu(ElaMenu* parentMenu);
    void createNavigateMenu(ElaMenu* parentMenu);

signals:
    void navigationRequest(const QString& pageName);
    void getAllPageKeysRequest();
public slots:
    void receiveAllPageKeys(const QMap<QString, QString>& pageKeys);

protected:

private:
    void connectionWithMainWindow();

    QMap<QString, QString> _pageKeys;
};

#endif // CONTEXTMENU_BASE_H
