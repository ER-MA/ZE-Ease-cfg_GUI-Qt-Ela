#include <QVBoxLayout>
#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>
#include <QMouseEvent>

#include "ElaComboBox.h"
#include "ElaPushButton.h"
#include "ElaTableView.h"
#include "ElaToolButton.h"
#include "ElaMenu.h"

#include "Model_ServerTable.h"
#include "Server_DataFetcher.h"
#include "ContextMenu_Base.h"

#include "Page_ServerList.h"

Page_ServerList::Page_ServerList(QWidget *parent)
    : Page_BasePage(parent)
{
    initUI();
    initData();
    initConnect();

    _contextMenu = createContextMenu(this);
}

Page_ServerList::~Page_ServerList()
{

}

const QString& Page_ServerList::pageName()
{
    static QString pageName("ServerList");
    return pageName;
}

void Page_ServerList::initUI()
{
    setWindowTitle("Server List");  // 窗口标题
    setTitleVisible(true);  // 标题栏是否可见
    setContentsMargins(20, 20, 20, 7);


    // toolBarWidget(工具栏)
    _serverComboBox = new ElaComboBox(this);
    QStringList comboList{
        "ExG",
        "风云社",
        "僵尸乐园",
        "UB 社区" };
    _serverComboBox->addItems(comboList);

    _joinGameButton = new ElaPushButton(this);
    _joinGameButton->setText("加入游戏");
    // 使用QDesktopServices::openUrl加入指定服务器
    connect(_joinGameButton, &ElaPushButton::clicked, this, [=]() {
        qDebug() << "[Page_ServerList] 开始加入游戏...";
        QString serverAddress = _fetcher->getServerAddressByRow(_currentSelectedRow); // 获取当前选择的服务器地址
        QString steamCommand = "steam://connect/" + serverAddress; // 组装steam连接命令
        qDebug() << "[Page_ServerList] 已执行steam命令: " << steamCommand;
        QUrl url(steamCommand);
        if (!QDesktopServices::openUrl(url)) {
            qDebug() << "[Page_ServerList] 打开steam连接失败...";
        }
    });

    _copyAddressButton = new ElaPushButton(this);
    _copyAddressButton->setText("复制地址");

    _moreOptionsButton = new ElaToolButton(this);
    _moreOptionsButton->setFixedHeight(35);
    _moreOptionsButton->setIsTransparent(false);
    _moreOptionsButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    _moreOptionsButton->setElaIcon(ElaIconType::Bars);
    //moreOptionsButton->setPopupMode(QToolButton::InstantPopup);
    //moreOptionsButton->setPopupMode(QToolButton::DelayedPopup);
    //moreOptionsButton->setPopupMode(QToolButton::MenuButtonPopup);
    //moreOptionsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //moreOptionsButton->setText("更多");
    ElaMenu* optionsMenu = new ElaMenu(this);
    optionsMenu->addElaIconAction(ElaIconType::Star, "收藏该地图");
    optionsMenu->addElaIconAction(ElaIconType::SquareInfo, "查看地图详情");
    optionsMenu->addElaIconAction(ElaIconType::CartShopping, "查看创意工坊");
    _moreOptionsButton->setMenu(optionsMenu);

    QWidget* toolBarWidget = new QWidget(this);
    QHBoxLayout* toolBarLayout = new QHBoxLayout(toolBarWidget);
    toolBarLayout->setContentsMargins(0, 0, 0, 0);
    toolBarLayout->addWidget(_serverComboBox);
    toolBarLayout->addStretch();
    toolBarLayout->addWidget(_joinGameButton);
    toolBarLayout->addWidget(_copyAddressButton);
    toolBarLayout->addWidget(_moreOptionsButton);


    // serverTableView(服务器列表)
    _serverTableView = new ElaTableView(this);
    _serverTableView->setHeaderMargin(10);  // 设置表头边距
    _serverTableView->horizontalHeader()->setStretchLastSection(true);  // 自动拉伸最后一列
    _serverTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);  // 允许拖动调整列宽
    _serverTableView->verticalHeader()->setVisible(false);  // 隐藏左侧序列号
    _serverTableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // 选择行为为行选择
    _serverTableView->setSelectionMode(QAbstractItemView::SingleSelection);  // 设置为仅单行选择
    _serverTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 大小策略为扩展
    connect(_serverTableView, &ElaTableView::tableViewShow, this, [=]() {
        _serverTableView->setColumnWidth(0, 135);
        _serverTableView->setColumnWidth(1, 300);
        _serverTableView->setColumnWidth(2, 300);
        _serverTableView->setColumnWidth(3, 100);
    });


    // centralWidget(中心窗口)
    createCustomWidget("选择服务器后加入游戏，或复制服务器地址自行输入控制台加入游戏");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("加入服务器");
    this->addCentralWidget(centralWidget, true, false, 0);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(toolBarWidget);
    centerVLayout->addWidget(_serverTableView);
}

void Page_ServerList::initData()
{
    // 服务器TableView - 设置Model
    _model = new Model_ServerTable(this);
    _serverTableView->setModel(_model); // 设置模型
    _fetcher = new Server_DataFetcher();
}

void Page_ServerList::initConnect()
{
    // 服务器ComboBox - 选择服务器
    connect(_serverComboBox, &ElaComboBox::currentIndexChanged, _fetcher, &Server_DataFetcher::setFetchServer);
    // 服务器TableView - 连接数据更新信号
    connect(_fetcher, &Server_DataFetcher::dataFetched, _model, &Model_ServerTable::fetchData);
    // 处理数据填充后选中行恢复逻辑
    connect(_fetcher, &Server_DataFetcher::dataFetched, this, [this]() {
        _isRestoringSelection = true; // 设置标志为true，表示正在恢复选中状态
        if (_currentSelectedRow >= 0 && _currentSelectedRow < _model->rowCount()) {
            _serverTableView->selectRow(_currentSelectedRow); // 恢复选中行
        }
        _isRestoringSelection = false; // 设置标志为false
    });

    // 服务器TableView - 连接选中行信号
    connect(_serverTableView->selectionModel(), &QItemSelectionModel::currentChanged, this, &Page_ServerList::onSelectionChanged);
}

void Page_ServerList::isCurrentPage(QString pageKey)
{
    if (property("ElaPageKey").toString() == pageKey)
    {
        _fetcher->startFetch();
    }
    else
    {
        _fetcher->stopFetch();
    }
}

void Page_ServerList::onSelectionChanged()
{
    if (_isRestoringSelection) {
        return;  // 如果正在恢复选中状态则返回
    }
    QModelIndex _currentSelectedIndex = _serverTableView->selectionModel()->currentIndex();
    _currentSelectedRow = _currentSelectedIndex.row();
    _currentSelectedCol = _currentSelectedIndex.column();
    qDebug() << "[Page_ServerList] 当前选中行/列号: " << _currentSelectedRow << "/" << _currentSelectedCol;

    if (_currentSelectedRow >= 0 && _currentSelectedRow < _model->rowCount()) {
        // TODO: 添加处理逻辑
        QString selectedContent = _model->data(_currentSelectedIndex, Qt::DisplayRole).toString(); // 获取选中数据
        qDebug() << "[Page_ServerList] 当前选中内容:" << selectedContent; // 输出选中的内容
    }
    else {
        qDebug() << "[Page_ServerList] 当前没有选中行";
    }
}



ElaMenu* Page_ServerList::createContextMenu(QWidget* parent)
{
    // 右键菜单
    ContextMenu_Base* contextMenu = new ContextMenu_Base(parent);

    contextMenu->createCommonToolMenu(contextMenu);

    contextMenu->addSeparator();
    // QKeySequence key = QKeySequence(Qt::CTRL | Qt::Key_S);
    contextMenu->addElaIconAction(ElaIconType::BoxCheck, "保存", QKeySequence::Save);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销", QKeySequence::Undo);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新", QKeySequence::Refresh);

    contextMenu->addElaIconAction(ElaIconType::Copy, "复制");

    contextMenu->addSeparator(); // --------

    contextMenu->createUnversalToolMenu(contextMenu);

    contextMenu->addSeparator(); // --------

    contextMenu->createNavigateMenu(contextMenu);

    return contextMenu;
}

void Page_ServerList::mouseReleaseEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::RightButton:
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        _contextMenu->popup(event->globalPosition().toPoint());
#else
        _contextMenu->popup(event->globalPos());
#endif
        break;
    }
    default:
    {
        break;
    }
    }
    ElaScrollPage::mouseReleaseEvent(event);
}
