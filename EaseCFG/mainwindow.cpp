#include "mainwindow.h"

#include <QApplication>

#include <QFile>
#include <QDebug>

#include "ElaContentDialog.h"
#include "ElaEventBus.h"
#include "ElaLog.h"

#include "Protal_Page.h"
#include "Promotion_Page.h"
#include "Page_ServerList.h"
#include "Keybind_Page.h"
#include "T_About.h"
#include "T_Setting.h"

#include <QSqlDatabase>


MainWindow::MainWindow(QWidget* parent)
    : ElaWindow(parent)
{
    initWindow();       // 主窗口
    initContent();      // 中心窗口内容
    initCloseDialog();  // 退出窗口配置
    initConnections();  // 连接信号槽

    testFunc();  // 测试函数
}

MainWindow::~MainWindow()
{
    delete this->_aboutPage;
}

void MainWindow::initWindow()
{
    //// 字体设置
    //QFontDatabase::addApplicationFont(":/Resource/Front/HarmonyOS_Sans/HarmonyOS_Sans_Regular.ttf");
    //// 修改默认字体为"Resource/Front/HarmonyOS_Sans/HarmonyOS_Sans_Regular.ttf"
    //QFont newFont = qApp->font();
    //newFont.setPointSize(12);
    //newFont.setFamily("Resource/Front/HarmonyOS_Sans/HarmonyOS_Sans_Regular.ttf");
    //qApp->setFont(newFont);

    // 窗口整体设置
    resize(1200, 740);  // 设置窗口大小
    setIsFixedSize(false);  // 设置窗口大小不固定
    // setIsEnableMica(true);  // 启用云母效果
    // setIsCentralStackedWidgetTransparent(true);  // 设置中心堆叠控件为透明
    // eApp->setThemeMode(ElaThemeType::Dark);  // 设置主题模式为暗黑模式
    // ElaLog::getInstance()->initMessageLog(true);  // 启用日志输出

    // 窗口状态栏
    // setIsStayTop(true);  // 窗口置顶
    setWindowIcon(QIcon(":/include/Image/Avatar-xujd_p7-128.jpg"));  // 设置窗口图标
    setWindowTitle("EaseCFG");  // 设置窗口标题
    // setWindowButtonFlag(ElaAppBarType::MinimizeButtonHint, false);  // 禁用最小化按钮

    // 左侧导航栏
    // setIsNavigationBarEnable(false);  // 禁用导航栏
    // setNavigationBarDisplayMode(ElaNavigationType::Compact);  // 设置导航栏模式为紧凑模式
    
    // 用户信息卡片
    // setUserInfoCardVisible(false);  // 隐藏用户信息卡片
    setUserInfoCardPixmap(QPixmap(":/Resource/Image/Avatar-xujd_p3-128.jpg"));  // 设置用户信息卡片图片
    setUserInfoCardTitle("鳕鱼煎蛋");  // 设置用户信息卡片标题
    setUserInfoCardSubTitle("随意使用 谢谢喵~");  // 设置用户信息卡片副标题

    moveToCenter();  // 移动到中心
}

void MainWindow::initContent()
{
    QString tempKey;

    _protalPage = new Protal_Page(this);
    _promotionPage = new Promotion_Page(this);
    _serverListPage = new Page_ServerList(this);
    _keyBindPage = new Keybind_Page(this);
    _settingPage = new T_Setting(this);

    addPageNode("主页", _protalPage, ElaIconType::House);
    addPageNode("推广", _promotionPage, ElaIconType::GlobePointer);
    addPageNode("服务器", _serverListPage, ElaIconType::Server);
    addPageNode("按键绑定", _keyBindPage, ElaIconType::Keyboard);
    addFooterNode("设置", _settingPage, tempKey, 0, ElaIconType::GearComplex);

    addFooterNode("关于", nullptr, _aboutPageKey, 0, ElaIconType::User);
    _aboutPage = new T_About();
    _aboutPage->hide();


}

void MainWindow::initCloseDialog()
{
    // 关闭弹窗
    _closeDialog = new ElaContentDialog(this);
    _closeDialog->setLeftButtonText("取消");      // 左侧按钮文字
    _closeDialog->setMiddleButtonText("最小化");   // 中间按钮文字
    _closeDialog->setRightButtonText("确定");     // 右侧按钮文字
    // 拦截默认关闭事件
    connect(_closeDialog, &ElaContentDialog::rightButtonClicked, this, &MainWindow::closeWindow);
    connect(_closeDialog, &ElaContentDialog::middleButtonClicked, this, &MainWindow::showMinimized);
    this->setIsDefaultClosed(false);
    connect(this, &MainWindow::closeButtonClicked, this, [=]() {
        _closeDialog->exec();
        }
    );
}

void MainWindow::initConnections()
{
    // 页面切换信号
    connect(this, &MainWindow::currentPageChanged, _serverListPage, &Page_ServerList::isCurrentPage);

    // 用户卡片被点击时
    connect(this, &MainWindow::userInfoCardClicked, this, [=]() {
        this->navigation(getPageKey(_protalPage));
    });

    // 导航栏页面或页脚节点被点击时触发的信号
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        updateCurrentPage(nodeKey);  // 更新当前页面

        if (_aboutPageKey == nodeKey)
        {
            // 关于页面被点击时
            _aboutPage->setFixedSize(400, 400);
            QRect rect = this->geometry(); // 包括标题栏和边框（还可使用rect()仅客户区）
            int x = this->x() + (rect.width() - _aboutPage->width()) / 2;
            int y = this->y() + (rect.height() - _aboutPage->height()) / 2;
            _aboutPage->move(x, y); // 设置关于页面的位置，位于窗口中心
            _aboutPage->show();
        }
    });

    this->navigation(getPageKey(_protalPage)); // 初始化导航到主页

    emit sendAllPageKeys(getAllPageKeys()); // 发送所有页面的key（必要！右键菜单需要用到，请在所有页面完成初始化后再发送信号）

    // 注册事件
    qDebug() << "[MainWindow::initConnections] 已注册的事件列表:" << ElaEventBus::getInstance()->getRegisteredEventsName();

}

// 更新所处页面
void MainWindow::updateCurrentPage(QString pageKey)
{
    _currentPageKey = pageKey;
    emit currentPageChanged(_currentPageKey);
    qDebug() << "[MainWindow::updateCurrentPage] 页面" << _currentPageKey << "为当前主窗口";
}

void MainWindow::testFunc()
{

}

QString MainWindow::getPageKey(QObject* page)
{
    if (page == nullptr)
    {
        return "";
    }
    return page->property("ElaPageKey").toString();
}

QMap<QString, QString> MainWindow::getAllPageKeys()
{
    QMap<QString, QString> pageKeys;

    pageKeys.insert(_protalPage->pageName(), getPageKey(_protalPage));
    pageKeys.insert(_promotionPage->pageName(), getPageKey(_promotionPage));
    pageKeys.insert(_serverListPage->pageName(), getPageKey(_serverListPage));
    pageKeys.insert(_keyBindPage->pageName(), getPageKey(_keyBindPage));
    pageKeys.insert(_settingPage->pageName(), getPageKey(_settingPage));

    qDebug() << "[MainWindow::getAllPageKeys] 所有页面的key: " << pageKeys;

    return pageKeys;
}

void MainWindow::navigateToPage(QString pageName)
{
    if (pageName.isEmpty() || pageName == Page_BasePage::pageName())
    {
        return;
    }
    this->navigation(getAllPageKeys()[pageName]);
}

// Slot:
void MainWindow::handleNavigationRequest(const QString& pageKey)
{
    navigateToPage(pageKey);
}

void MainWindow::handleGetAllPageKeysRrequest()
{
    emit sendAllPageKeys(getAllPageKeys());
    qDebug() << "[MainWindow::handleGetAllPageKeysRrequest] pageKeys: " << getAllPageKeys();
}
