#ifndef PROMOTION_PAGE_H
#define PROMOTION_PAGE_H

#include "Page_BasePage.h"

struct PromotionCardParams {
    QString cardTitle;
    QString promotionTitle;
    QString title;
    QString subTitle;
    QPixmap cardPixmap;
};

class Page_BasePage;
class QMouseEvent;
class ElaMenu;
class ElaPromotionCard;
class ElaPromotionView;
class ElaFlowLayout;
class Promotion_Page : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Promotion_Page(QWidget* parent = nullptr);

    static const QString& pageName();

protected:

    void onPageContexMenu(const QPoint& pos);

    // 视频卡片组件

    ElaPromotionCard* createVideoCard(QWidget* parent, const PromotionCardParams& param);
    QList<ElaPromotionCard*> createVideoCard(QWidget* parent, const QList<PromotionCardParams>& params);

    void onVideoCardContextMenu(const QPoint& pos);

    QVBoxLayout* createVideoComponent(QWidget* parent, const QString& title, const QList<PromotionCardParams>& videoCardParams);

    void addVideoCard(const PromotionCardParams& params);
    void addVideoCard(const QList<PromotionCardParams>& params);

    void removeVideoCard(ElaPromotionCard* card);



    // 轮播图组件

    ElaPromotionCard* createBannerCard(QWidget* parent, const PromotionCardParams& param);
    void onBannerCardContextMenu(const QPoint& pos);
    ElaPromotionView* createBannerComponent(QWidget* parent, const QList<PromotionCardParams>& params);
    ElaPromotionView* createBannerComponent(QWidget* parent, const QList<ElaPromotionCard*>& promotionCards);

private:
    void InitializeUI();
    void InitializeData();
    void InitializeConnect();

    ElaFlowLayout* _videoFlowLayout;  // 视频卡片的流式布局
    QList<ElaPromotionCard*> _videoCards; // 当前所有视频卡片
};


#endif // PROMOTION_PAGE_H
