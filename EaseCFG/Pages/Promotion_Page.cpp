#include "Promotion_Page.h"

#include "Page_BasePage.h"
#include "ContextMenu_Base.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

#include "ElaPromotionCard.h"
#include "ElaPromotionView.h"
#include "ElaText.h"
#include "ElaPopularCard.h"
#include "ElaFlowLayout.h"

Promotion_Page::Promotion_Page(QWidget *parent) :
    Page_BasePage(parent)
{
    InitializeUI();
    InitializeData();
    InitializeConnect();
}

const QString& Promotion_Page::pageName()
{
    static QString pageName("Promotion");
    return pageName;
}

void Promotion_Page::InitializeUI()
{
    setWindowTitle("Promotion Page"); // 窗口标题
    setContentsMargins(20, 20, 20, 7);

    QList<PromotionCardParams> promotionCardParamsList = {
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        }
    };

    ElaPromotionView* promotionView = createBannerComponent(this, promotionCardParamsList);

    QList<PromotionCardParams> videoPromotionCardParamsList = {
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        },
        {
            "CardTitle",
            "PromotionTitle",
            "Title",
            "SubTitle",
            QPixmap(":/Resource/Image/Card/miku.png")
        }
    };
    QVBoxLayout* videoCardComponent = createVideoComponent(this, "直播推荐", videoPromotionCardParamsList);

    setTitleVisible(true); // 标题栏是否可见
    createCustomWidget("直播、视频分享；及社区活动推广");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("社区推广");
    this->addCentralWidget(centralWidget, true, true, 0);

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(promotionView);
    centerVLayout->addLayout(videoCardComponent);
    centerVLayout->addStretch();
}

void Promotion_Page::InitializeData()
{

}

void Promotion_Page::InitializeConnect()
{
    // 页面右键菜单
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested,
            this, &Promotion_Page::onPageContexMenu);
}

void Promotion_Page::onPageContexMenu(const QPoint& pos)
{
    // 获取触发右键菜单的卡片控件
    QWidget* senderWidget = qobject_cast<QWidget*>(sender());
    if (!senderWidget) return;

    // 右键菜单
    ContextMenu_Base* contextMenu = new ContextMenu_Base(this);
    contextMenu->createCommonToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    contextMenu->addElaIconAction(ElaIconType::BoxCheck, "保存", QKeySequence::Save);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销", QKeySequence::Undo);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新", QKeySequence::Refresh);
    contextMenu->addSeparator(); // --------
    contextMenu->createUnversalToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    contextMenu->createNavigateMenu(contextMenu);

    // 使用卡片自身的坐标系转换全局位置
    contextMenu->popup(senderWidget->mapToGlobal(pos));
}

ElaPromotionCard* Promotion_Page::createVideoCard(QWidget* parent, const PromotionCardParams& param)
{
    ElaPromotionCard* promotionCard = new ElaPromotionCard(parent);

    promotionCard->setBorderRadius(5);
    promotionCard->setFixedSize(272, 153);
    promotionCard->setCardPixmap(QPixmap(param.cardPixmap));
    // 左上角标题
    promotionCard->setCardTitle(param.cardTitle);
    promotionCard->setCardTitlePixelSize(22);
    promotionCard->setCardTitleColor(Qt::white);
    // 左侧促销标签
    promotionCard->setPromotionTitle(param.promotionTitle);
    promotionCard->setPromotionTitlePixelSize(12);
    promotionCard->setPromotionTitleColor(Qt::white);
    promotionCard->setPromotionTitleBaseColor(QColor(0, 0, 0, 120));
    // 左侧标题
    promotionCard->setTitle(param.title);
    promotionCard->setTitlePixelSize(25);
    promotionCard->setTitleColor(Qt::white);
    // 左侧副标题
    promotionCard->setSubTitle(param.subTitle);
    promotionCard->setSubTitlePixelSize(16);
    promotionCard->setSubTitleColor(Qt::white);

    // 添加右键菜单功能
    promotionCard->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(promotionCard, &QWidget::customContextMenuRequested,
            this, &Promotion_Page::onVideoCardContextMenu);

    return promotionCard;
}

QList<ElaPromotionCard*> Promotion_Page::createVideoCard(QWidget* parent, const QList<PromotionCardParams>& params)
{
    QList<ElaPromotionCard*> promotionCards;

    for (const auto& param : params)
    {
        ElaPromotionCard* promotionCard = createVideoCard(parent, param);
        promotionCards.append(promotionCard);
    }

    return promotionCards;
}

void Promotion_Page::onVideoCardContextMenu(const QPoint& pos)
{
    // 获取触发右键菜单的卡片控件
    QWidget* senderWidget = qobject_cast<QWidget*>(sender());
    if (!senderWidget) return;

    // 右键菜单
    ContextMenu_Base* contextMenu = new ContextMenu_Base(this);
    contextMenu->createCommonToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    QAction* routeBack = contextMenu->addElaIconAction(ElaIconType::ArrowTurnLeft, "删除", QKeySequence::Back);
    connect(routeBack, &QAction::triggered, this, [=]() {
        removeVideoCard(qobject_cast<ElaPromotionCard*>(senderWidget));
    });
    contextMenu->addSeparator(); // --------
    contextMenu->createUnversalToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    contextMenu->createNavigateMenu(contextMenu);

    // 计算全局坐标和菜单尺寸
    QPoint globalPos = senderWidget->mapToGlobal(pos);
    contextMenu->adjustSize(); // 确保获取正确尺寸
    QSize menuSize = contextMenu->sizeHint();

    // 获取当前屏幕可用区域
    QRect screenGeometry = QApplication::screenAt(globalPos)->availableGeometry();

    // 检查下方空间是否足够
    if (globalPos.y() + menuSize.height() > screenGeometry.bottom()) {
        // 空间不足，改为向上弹出（以菜单底部对齐点击位置）
        globalPos.setY(globalPos.y() - menuSize.height());
    }

    // 处理横向溢出
    if (globalPos.x() + menuSize.width() > screenGeometry.right()) {
        globalPos.setX(screenGeometry.right() - menuSize.width());
    }

    contextMenu->popup(globalPos);
}

QVBoxLayout* Promotion_Page::createVideoComponent(QWidget* parent, const QString& title, const QList<PromotionCardParams>& videoCardParams)
{
    // - 标题
    ElaText* flowText = new ElaText(title, parent);
    flowText->setTextPixelSize(20);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(0, 0, 0, 0);
    flowTextLayout->addWidget(flowText);


    QList<ElaPromotionCard*> promotionCards = createVideoCard(parent, videoCardParams);

    ElaFlowLayout* flowLayout = new ElaFlowLayout(0, 5, 5);
    flowLayout->setContentsMargins(0, 0, 0, 0);
    flowLayout->setIsAnimation(true);
    for (auto card : promotionCards) {
        flowLayout->addWidget(card);
    }

    // 推荐卡片区域
    QVBoxLayout* middleLayout = new QVBoxLayout();
    middleLayout->setContentsMargins(0, 0, 0, 0);
    middleLayout->addLayout(flowTextLayout);
    middleLayout->addLayout(flowLayout);

    // 保存流式布局和卡片列表到成员变量（使其支持动态增删）
    _videoFlowLayout = flowLayout;
    _videoCards = promotionCards;

    return middleLayout;
}

void Promotion_Page::addVideoCard(const PromotionCardParams& params)
{
    ElaPromotionCard* newCard = createVideoCard(this, params);
    _videoCards.append(newCard);
    _videoFlowLayout->addWidget(newCard);
    _videoFlowLayout->update(); // 更新布局
}

void Promotion_Page::addVideoCard(const QList<PromotionCardParams>& params)
{
    for (const auto& param : params) {
        addVideoCard(param);
    }
}

void Promotion_Page::removeVideoCard(ElaPromotionCard* card) {
    if (_videoCards.removeOne(card)) {
        _videoFlowLayout->removeWidget(card);
        card->deleteLater();
        _videoFlowLayout->update(); // 更新布局
    }
}

ElaPromotionCard* Promotion_Page::createBannerCard(QWidget* parent, const PromotionCardParams& param)
{
    ElaPromotionCard* promotionCard = new ElaPromotionCard(parent);

    promotionCard->setBorderRadius(5);
    promotionCard->setFixedSize(715, 300);
    promotionCard->setCardPixmap(QPixmap(param.cardPixmap));
    // 左上角标题
    promotionCard->setCardTitle(param.cardTitle);
    promotionCard->setCardTitlePixelSize(22);
    promotionCard->setCardTitleColor(Qt::white);
    // 左侧促销标签
    promotionCard->setPromotionTitle(param.promotionTitle);
    promotionCard->setPromotionTitlePixelSize(12);
    promotionCard->setPromotionTitleColor(Qt::white);
    promotionCard->setPromotionTitleBaseColor(QColor(0, 0, 0, 120));
    // 左侧标题
    promotionCard->setTitle(param.title);
    promotionCard->setTitlePixelSize(25);
    promotionCard->setTitleColor(Qt::white);
    // 左侧副标题
    promotionCard->setSubTitle(param.subTitle);
    promotionCard->setSubTitlePixelSize(16);
    promotionCard->setSubTitleColor(Qt::white);

    // 添加右键菜单功能
    promotionCard->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(promotionCard, &QWidget::customContextMenuRequested,
            this, &Promotion_Page::onBannerCardContextMenu);

    return promotionCard;
}

void Promotion_Page::onBannerCardContextMenu(const QPoint& pos)
{
    // 获取触发右键菜单的卡片控件
    QWidget* senderWidget = qobject_cast<QWidget*>(sender());
    if (!senderWidget) return;

    // 右键菜单
    ContextMenu_Base* contextMenu = new ContextMenu_Base(this);
    contextMenu->createCommonToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    QAction* routeBack = contextMenu->addElaIconAction(ElaIconType::ArrowTurnLeft, "你好", QKeySequence::Back);
    connect(routeBack, &QAction::triggered, this, [=]() {
        
    });
    contextMenu->addSeparator(); // --------
    contextMenu->createUnversalToolMenu(contextMenu);
    contextMenu->addSeparator(); // --------
    contextMenu->createNavigateMenu(contextMenu);

    // 使用卡片自身的坐标系转换全局位置
    contextMenu->popup(senderWidget->mapToGlobal(pos));
}

ElaPromotionView* Promotion_Page::createBannerComponent(QWidget* parent, const QList<PromotionCardParams>& params)
{
    ElaPromotionView* promotionView = new ElaPromotionView(parent);

    for (const auto& param : params)
    {
        ElaPromotionCard* promotionCard = createBannerCard(parent, param);
        promotionView->appendPromotionCard(promotionCard);
    }
    // 主要展示卡片
    promotionView->setCardExpandWidth(650);
    // 次要展示卡片
    promotionView->setCardCollapseWidth(300);

    promotionView->setIsAutoScroll(true); // 是否自动滚动
    promotionView->setAutoScrollInterval(400); // 是否自动滚动

    return promotionView;
}

ElaPromotionView* Promotion_Page::createBannerComponent(QWidget* parent, const QList<ElaPromotionCard*>& promotionCards)
{
    ElaPromotionView* promotionView = new ElaPromotionView(parent);

    for (const auto& promotionCard : promotionCards)
    {
        promotionView->appendPromotionCard(promotionCard);
    }

    return promotionView;
}
