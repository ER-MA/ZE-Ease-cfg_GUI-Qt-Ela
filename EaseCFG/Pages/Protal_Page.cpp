#include "Protal_Page.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ElaText.h"
#include "ElaImageCard.h"
#include "ElaAcrylicUrlCard.h"
#include "ElaToolTip.h"
#include "ElaScrollArea.h"

Protal_Page::Protal_Page(QWidget *parent) :
    Page_BasePage(parent)
{
    InitializeUI();
    InitializeData();
    InitializeConnect();
}

void Protal_Page::InitializeUI()
{
    setWindowTitle("Protal Page"); // 窗口标题
    setContentsMargins(2, 2, 0, 7);


    // 标题卡片区域
    ElaText* desText = new ElaText("欢迎来到CSGO社区集散地", this);
    desText->setTextPixelSize(18);
    ElaText* titleText = new ElaText("社区主页", this);
    titleText->setTextPixelSize(35);

    QVBoxLayout* titleLayout = new QVBoxLayout();
    titleLayout->setContentsMargins(20, 20, 0, 0);
    titleLayout->addWidget(desText);
    titleLayout->addWidget(titleText);

    ElaImageCard* backgroundCard = new ElaImageCard(this);
    backgroundCard->setBorderRadius(10);
    backgroundCard->setFixedHeight(320);
    backgroundCard->setMaximumAspectRatio(1.7);
    backgroundCard->setCardImage(QImage(":/Resource/Image/Home_Background.png"));

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
    QList<ElaAcrylicUrlCard*> urlCards = createUrlCards(this, params);

    ElaScrollArea* cardScrollArea = new ElaScrollArea(this);
    cardScrollArea->setWidgetResizable(true);
    cardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardScrollArea->setIsGrabGesture(true, 0);  // 启用手势滚动
    cardScrollArea->setIsOverShoot(Qt::Horizontal, true); // 允许水平过冲
    cardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); // 显示滚动条
    QWidget* cardScrollAreaWidget = new QWidget(this);
    cardScrollAreaWidget->setStyleSheet("background-color:transparent;");
    cardScrollArea->setWidget(cardScrollAreaWidget);
    QHBoxLayout* urlCardLayout = new QHBoxLayout();
    urlCardLayout->setSpacing(15);
    urlCardLayout->setContentsMargins(30, 0, 30, 20);
    for (auto card : urlCards) {
        urlCardLayout->addWidget(card);
    }
    urlCardLayout->addStretch();
    QVBoxLayout* cardScrollAreaWidgetLayout = new QVBoxLayout(cardScrollAreaWidget);
    cardScrollAreaWidgetLayout->setContentsMargins(0, 0, 0, 0);
    cardScrollAreaWidgetLayout->addStretch();
    cardScrollAreaWidgetLayout->addLayout(urlCardLayout);

    QVBoxLayout* backgroundLayout = new QVBoxLayout(backgroundCard);
    backgroundLayout->setContentsMargins(0, 0, 0, 0);
    backgroundLayout->addLayout(titleLayout);
    backgroundLayout->addWidget(cardScrollArea);


    setTitleVisible(false); // 隐藏标题栏
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Protal Page111");

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(backgroundCard);
    centerVLayout->addSpacing(20);
    centerVLayout->addStretch();

    this->addCentralWidget(centralWidget, true, true, 0); // 第三个参数为：是否启用手势滚动
}

void Protal_Page::InitializeData()
{

}

void Protal_Page::InitializeConnect()
{

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
