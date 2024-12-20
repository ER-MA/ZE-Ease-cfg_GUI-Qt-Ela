#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "ElaWindow.h"


class Page_KeyBind;
class Page_ServerList;
class T_About;
class T_Setting;
class ElaContentDialog;
class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initWindow();
    void initContent();
    void initCloseDialog();
    void initConnections();
    void updateCurrentPage(QString pageKey);

signals: // 信号
    void currentPageChanged(QString pageKey);

private:
    Page_ServerList* _serverListPage{nullptr};
    Page_KeyBind* _keyBindPage{nullptr};
    T_About* _aboutPage{nullptr};
    T_Setting* _settingPage{nullptr};

    QString _serverListPageKey{""};
    QString _keyBindPageKey{""};
    QString _aboutPageKey{""};
    QString _settingPageKey{""};

    ElaContentDialog* _closeDialog{nullptr};
};
#endif // MAINWINDOW_H
