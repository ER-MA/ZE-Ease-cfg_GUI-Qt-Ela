#ifndef Page_SERVERLIST_H
#define Page_SERVERLIST_H

#include "Page_BasePage.h"

#include "ElaComboBox.h"
#include "ElaPushButton.h"
#include "ElaTableView.h"
#include "ElaToolButton.h"
#include "ElaMenu.h"

#include "Model_ServerTable.h"
#include "Server_DataFetcher.h"

class Page_ServerList : public Page_BasePage
{
    Q_OBJECT

public:
    explicit Page_ServerList(QWidget* parent = nullptr);
    ~Page_ServerList();

    static const QString& pageName();

    void initUI();
    void initData();
    void initConnect();

signals:
    void fetchData();

public slots:
    void isCurrentPage(QString pageKey);
    void onSelectionChanged();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    // 成员变量
    ElaComboBox* _serverComboBox;
    ElaPushButton* _joinGameButton;
    ElaPushButton* _copyAddressButton;
    ElaToolButton* _moreOptionsButton;
    ElaTableView* _serverTableView;
    Model_ServerTable* _model;
    Server_DataFetcher* _fetcher;

    QModelIndex _currentSelectedIndex;
    int _currentSelectedRow = -1;
    int _currentSelectedCol = -1;
    bool _isRestoringSelection = false;

    ElaMenu* createContextMenu(QWidget* parent);
    ElaMenu* _contextMenu;
};


#endif // Page_SERVERLIST_H
