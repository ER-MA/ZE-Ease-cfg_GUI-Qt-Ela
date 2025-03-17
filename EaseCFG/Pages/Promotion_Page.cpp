#include "Promotion_Page.h"

#include "Page_BasePage.h"
#include "ContextMenu_Base.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

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

    ElaPromotionView* promotionView = createPromotionView(this, promotionCardParamsList);

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
    QVBoxLayout* videoCardComponent = createVideoCardComponent(this, "直播推荐", videoPromotionCardParamsList);

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

    _contextMenu = createContextMenu(this);
}

void Promotion_Page::InitializeData()
{

}

void Promotion_Page::InitializeConnect()
{

}

ElaMenu* Promotion_Page::createContextMenu(QWidget* parent)
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

void Promotion_Page::mouseReleaseEvent(QMouseEvent* event)
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

QVBoxLayout* Promotion_Page::createVideoCardComponent(QWidget* parent, const QString& title, const QList<PromotionCardParams>& videoCardParams)
{
    // - 标题
    ElaText* flowText = new ElaText(title, parent);
    flowText->setTextPixelSize(20);
    QHBoxLayout* flowTextLayout = new QHBoxLayout();
    flowTextLayout->setContentsMargins(0, 0, 0, 0);
    flowTextLayout->addWidget(flowText);


    QList<ElaPromotionCard*> promotionCards = createVideoPromotionCard(parent, videoCardParams);

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

    return middleLayout;
}

ElaPromotionCard* Promotion_Page::createVideoPromotionCard(QWidget* parent, const PromotionCardParams& param)
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

    return promotionCard;
}

QList<ElaPromotionCard*> Promotion_Page::createVideoPromotionCard(QWidget* parent, const QList<PromotionCardParams>& params)
{
    QList<ElaPromotionCard*> promotionCards;

    for (const auto& param : params)
    {
        ElaPromotionCard* promotionCard = createVideoPromotionCard(parent, param);
        promotionCards.append(promotionCard);
    }

    return promotionCards;
}

ElaPromotionCard* Promotion_Page::createPromotionCard(QWidget* parent, const PromotionCardParams& param)
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

    return promotionCard;
}

ElaPromotionView* Promotion_Page::createPromotionView(QWidget* parent, const QList<PromotionCardParams>& params)
{
    ElaPromotionView* promotionView = new ElaPromotionView(parent);

    for (const auto& param : params)
    {
        ElaPromotionCard* promotionCard = createPromotionCard(parent, param);
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

ElaPromotionView* Promotion_Page::createPromotionView(QWidget* parent, const QList<ElaPromotionCard*>& promotionCards)
{
    ElaPromotionView* promotionView = new ElaPromotionView(parent);

    for (const auto& promotionCard : promotionCards)
    {
        promotionView->appendPromotionCard(promotionCard);
    }

    return promotionView;
}
