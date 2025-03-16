#include "Protal_Page.h"
#include "mainwindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMouseEvent>
#include <QUrl>
#include <QDesktopServices>

#include "ElaTheme.h"
#include "ElaText.h"
#include "ElaMenu.h"
#include "ElaIcon.h"
#include "ElaImageCard.h"
#include "ElaAcrylicUrlCard.h"
#include "ElaToolTip.h"
#include "ElaScrollArea.h"
#include "ElaPopularCard.h"
#include "ElaFlowLayout.h"
#include "ElaNavigationRouter.h"

#include "ContextMenu_Base.h"

Protal_Page::Protal_Page(MainWindow* mainWindow, QWidget* parent) :
    Page_BasePage(parent),
    _mainWindowPtr(mainWindow)
{
    initializeUI();
    initializeData();
    initializeConnect();
}

const QString& Protal_Page::pageName()
{
    static QString pageName("Protal");
    return pageName;
}

void Protal_Page::initializeUI()
{
    setWindowTitle("Protal Page"); // 窗口标题
    setContentsMargins(2, 2, 0, 7);
    setTitleVisible(false); // 隐藏标题栏
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("社区门户");

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(createTopComponent(this));
    centerVLayout->addSpacing(10);
    centerVLayout->addLayout(createMiddleComponent(this));
    centerVLayout->addStretch();

    this->addCentralWidget(centralWidget, true, true, 0); // 第三个参数为：是否启用手势滚动

    _contextMenu = createContextMenu(this); // 创建右键菜单

}

void Protal_Page::initializeData()
{

}

void Protal_Page::initializeConnect()
{

}

ElaImageCard* Protal_Page::createTopComponent(QWidget* parent)
{
    // - 背景
    ElaImageCard* backgroundCard = new ElaImageCard(parent);
    backgroundCard->setBorderRadius(10);
    backgroundCard->setFixedHeight(320);
    backgroundCard->setMaximumAspectRatio(1.7);
    backgroundCard->setCardImage(QImage(":/Resource/Image/Home_Background.png"));

    // - 标题
    ElaText* desText = new ElaText("欢迎来到CSGO社区集散地", parent);
    desText->setTextPixelSize(18);
    ElaText* titleText = new ElaText("社区主页", parent);
    titleText->setTextPixelSize(35);

    QVBoxLayout* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(20, 20, 0, 0);
    titleLayout->addWidget(desText);
    titleLayout->addWidget(titleText);

    // - 链接卡片

    QWidget* cardScrollAreaWidget = new QWidget(parent);
    cardScrollAreaWidget->setStyleSheet("background-color:transparent;");

    ElaScrollArea* cardScrollArea = new ElaScrollArea(parent);
    cardScrollArea->setWidgetResizable(true);
    cardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    cardScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setIsGrabGesture(true, 0);  // 启用手势滚动
    cardScrollArea->setIsOverShoot(Qt::Horizontal, true); // 允许水平过冲
    cardScrollArea->setWidget(cardScrollAreaWidget);

    QHBoxLayout* urlCardLayout = new QHBoxLayout();
    urlCardLayout->setSpacing(15);
    urlCardLayout->setContentsMargins(30, 0, 30, 10);
    QList<UrlCardParams> params = {
        {
            "ExG 社区",
            "中国 GMOD / CS2 娱乐服务器",
            ":/Resource/Image/CommunityMaterial/ExG_Logo.webp",
            "https://darkrp.cn/",
            "在浏览器中访问 ExG 社区主页"
        },
        {
            "Fys 风云社",
            "暂无简介",
            ":/Resource/Image/CommunityMaterial/FyS_Logo.png",
            "https://fyscs.com/",
            "在浏览器中访问 Fys 风云社主页"
        },
        {
            "MoeUB 社区",
            "成立于2012年的老牌社区，主打 CSGO 僵尸逃跑 等服务器",
            ":/Resource/Image/CommunityMaterial/MoeUB_Logo.svg",
            "https://csgo.moeub.cn/",
            "在浏览器中访问 MoeUB 社区主页"
        },
        {
            "僵尸乐园",
            "建立于2007年初，一直致力为玩家提供模式丰富的CS起源/CS:GO服务器",
            ":/Resource/Image/CommunityMaterial/ZED_Logo_KirisameMarisa.png",
            "https://zombieden.cn/",
            "在浏览器中访问 Zombie Den 僵尸乐园主页"
        },
        {
            "星社区",
            "暂无简介",
            ":/Resource/Image/CommunityMaterial/HoshiStar_Logo.png",
            "https://www.hoshics.com/",
            "在浏览器中访问 Hoshi-Star 星社区主页"
        },
        {
            "起源方舟",
            "暂无简介",
            ":/Resource/Image/CommunityMaterial/SourceArk_Logo.png",
            "http://s2ark.com/",
            "在浏览器中访问 Source Ark 起源方舟主页"
        },
        {
            "CNGOKZ",
            "欢迎加入CNGOKZ大家庭，也许是最纯净的KZ社区私服",
            ":/Resource/Image/CommunityMaterial/CNGOKZ_Logo.jpg",
            "https://cngokz.com/",
            "在浏览器中访问 CNGOKZ 社区主页"
        },
        {
            "X 社区",
            "【X】社区是一个以娱乐为主的CSGO社区服务器",
            ":/Resource/Image/CommunityMaterial/93X_Logo.jpg",
            "https://bbs.upkk.com/",
            "在浏览器中访问 UPKK 社区论坛"
        },
        {
            "GitHub仓库",
            "访问软件源码",
            ":/Resource/Image/github.png",
            "https://github.com/ER-MA/ZE-Ease-cfg_GUI-Qt-Ela",
            "跳转到 GitHub 仓库"
        },
        {
            "作者主页",
            "联系开发者",
            ":/Resource/Image/Avatar-xujd_p3-128.jpg",
            "https://space.bilibili.com/624753909",
            "访问B站主页"
        }
    };
    QList<ElaAcrylicUrlCard*> urlCards = createUrlCards(parent, params);
    for (auto card : urlCards) {
        urlCardLayout->addWidget(card);
    }
    urlCardLayout->addStretch();

    QVBoxLayout* cardScrollAreaWidgetLayout = new QVBoxLayout(cardScrollAreaWidget);
    cardScrollAreaWidgetLayout->setContentsMargins(0, 0, 0, 0);
    cardScrollAreaWidgetLayout->addStretch();
    cardScrollAreaWidgetLayout->addLayout(urlCardLayout);

    // 标题卡片区域
    QVBoxLayout* backgroundLayout = new QVBoxLayout(backgroundCard);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addLayout(titleLayout);
    backgroundLayout->addWidget(cardScrollArea);

    return backgroundCard;
}

QVBoxLayout* Protal_Page::createMiddleComponent(QWidget* parent)
{
    // - 标题
    ElaText* flowText = new ElaText("开启你的社区旅途", parent);
    flowText->setTextPixelSize(20);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(20, 0, 0, 0);
    flowTextLayout->addWidget(flowText);

    // - 推荐卡片
    QList<PopularCardParams> params = {
        {
            "服务器列表",
            "👉 点我寻找服务器",
            "本地工具",
            ":/Resource/Image/control/ListView.png",
            "在这里选择你喜欢的服务器，一键加入游戏。支持地图查询和订阅哦！",
            "跳转",
            ":/Resource/Image/IARC/IARC_12+.svg.png",
            //[this]() {
            //    Q_EMIT pageServerListNavigation();
            //}
            QUrl("https://space.bilibili.com/624753909")
        },
        {
            "按键绑定",
            "💪 想成为高手吗？点我",
            "本地工具",
            ":/Resource/Image/control/AppBarSeparator.png",
            "目前最为强大的CSGO按键绑定工具，提供了多数社区的所有常用和进阶功能。傻瓜式配置，简单易用。",
            "跳转",
            ":/Resource/Image/IARC/IARC_12+.svg.png",
            //[this]() {
            //    Q_EMIT pageKeyBindNavigation();
            //}
            QUrl("https://space.bilibili.com/624753909")
        },
        {
            "联系作者",
            "💭 有什么疑问？点这",
            "网页链接",
            ":/Resource/Image/control/AutomationProperties.png",
            "有什么疑问或者建议吗？欢迎来我B站主页与我联系。",
            "前往",
            ":/Resource/Image/IARC/IARC_12+.svg.png",
            QUrl("https://space.bilibili.com/624753909")
        },
        {
            "加入我们",
            "⭐ 裘裘了！点个Start吧",
            "网页链接",
            ":/Resource/Image/control/Flyout.png",
            "我们需要你的帮助！欢迎加入我们，一起完善它。这是Github仓库链接，本项目完全开源哦~",
            "前往",
            ":/Resource/Image/IARC/IARC_12+.svg.png",
            QUrl("https://github.com/ER-MA/ZE-Ease-cfg_GUI-Qt-Ela")
        },
        {
            "Placeholder",
            "🌐 subtitle",
            "Tips",
            ":/Resource/Image/control/AppBarButton.png",
            "Detail text...",
            "Button",
            ":/Resource/Image/IARC/IARC_18+.svg.png",
            [this]() {
                qDebug() << "[PopularCard:Placeholder] Clicked";
            }
        }
    };
    QList<ElaPopularCard*> popCards = createPopularCards(parent, params);

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setContentsMargins(25, 0, 0, 0);
    flowLayout->setIsAnimation(true);
    for (auto card : popCards) {
        flowLayout->addWidget(card);
    }

    // 推荐卡片区域
    QVBoxLayout* middleLayout = new QVBoxLayout();
    middleLayout->setContentsMargins(0, 0, 0, 0);
    middleLayout->addLayout(flowTextLayout);
    middleLayout->addLayout(flowLayout);

    return middleLayout;
}

QList<ElaAcrylicUrlCard*> Protal_Page::createUrlCards(QWidget* parent, const QList<UrlCardParams>& params)
{
    QList<ElaAcrylicUrlCard*> cards;

    for (const auto& param : params) {
        // 创建卡片实例
        ElaAcrylicUrlCard* card = new ElaAcrylicUrlCard(parent);

        // 设置默认样式参数
        card->setFixedSize(192, 180);
        card->setBorderRadius(8);
        card->setMainOpacity(0.95);
        card->setNoiseOpacity(0.06);
        card->setBrushAlpha(245);
        card->setCardPixmapSize(64, 64);
        card->setCardPixMode(ElaCardPixType::RoundedRect);
        card->setCardPixmapBorderRadius(8);
        card->setTitleSpacing(6);
        card->setTitlePixelSize(18);
        card->setSubTitleSpacing(6);
        card->setSubTitlePixelSize(12);

        // 设置传入参数
        card->setTitle(param.title);
        card->setSubTitle(param.subtitle);
        card->setCardPixmap(QPixmap(param.imagePath));
        card->setUrl(param.url);

        // 添加悬浮提示
        ElaToolTip* tooltip = new ElaToolTip(card);
        tooltip->setToolTip(param.tooltip);

        cards.append(card);
    }

    return cards;
}

QList<ElaPopularCard*> Protal_Page::createPopularCards(QWidget* parent, const QList<PopularCardParams>& params)
{
    QList<ElaPopularCard*> cards;

    for (const auto& param : params) {
        ElaPopularCard* card = new ElaPopularCard(parent);

        qDebug() << "创建卡片：" << param.title;
        // 设置基础参数
        card->setBorderRadius(8);
        card->setTitle(param.title);
        card->setSubTitle(param.subtitle);
        card->setInteractiveTips(param.interactiveTips);
        card->setDetailedText(param.detailedText);
        card->setCardButtontext(param.buttonText);
        card->setCardPixmap(QPixmap(param.imagePath));
        card->setCardFloatPixmap(QPixmap(param.floatImagePath));

        // 设置交互行为
        std::visit([card, parent](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, std::function<void()>>) {
                // 通用回调模式
                QObject::connect(card, &ElaPopularCard::popularCardButtonClicked, parent, arg);
                QObject::connect(card, &ElaPopularCard::popularCardClicked, parent, arg);
            }
            else if constexpr (std::is_same_v<T, QUrl>) {
                // 直接打开URL
                QObject::connect(card, &ElaPopularCard::popularCardButtonClicked, parent, [url = arg]() {
                    QDesktopServices::openUrl(url);
                });
                QObject::connect(card, &ElaPopularCard::popularCardClicked, parent, [url = arg]() {
                    QDesktopServices::openUrl(url);
                });
            }
        }, param.action);

        cards.append(card);
    }

    return cards;
}

ElaMenu* Protal_Page::createContextMenu(QWidget* parent)
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

void Protal_Page::mouseReleaseEvent(QMouseEvent* event)
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
