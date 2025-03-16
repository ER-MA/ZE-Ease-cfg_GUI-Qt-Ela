#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ElaWindow.h"

class Protal_Page;
class Promotion_Page;
class Page_ServerList;
class Keybind_Page;
class T_About;
class T_Setting;
class ElaContentDialog;
class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void updateCurrentPage(QString pageKey);

    void testFunc();


signals: // 信号
    void currentPageChanged(QString pageKey);
    void sendAllPageKeys(QMap<QString, QString> pageKey);

public slots: // 槽函数
    void handleNavigationRequest(const QString& pageKey);
    void handleGetAllPageKeysRrequest();

private:
    void initWindow();
    void initContent();
    void initCloseDialog();
    void initConnections();

    QString getPageKey(QObject* page);
    QMap<QString, QString> getAllPageKeys();
    void navigateToPage(QString pageKey);

    Protal_Page* _protalPage{nullptr};
    Promotion_Page* _promotionPage{nullptr};
    Page_ServerList* _serverListPage{nullptr};
    Keybind_Page* _keyBindPage{nullptr};
    T_About* _aboutPage{nullptr};
    T_Setting* _settingPage{nullptr};

    QString _aboutPageKey{""};

    QString _currentPageKey{""};

    ElaContentDialog* _closeDialog{nullptr};
};
#endif // MAINWINDOW_H
