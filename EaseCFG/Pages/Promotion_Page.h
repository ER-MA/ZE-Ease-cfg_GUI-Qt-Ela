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
class Promotion_Page : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Promotion_Page(QWidget* parent = nullptr);

    static const QString& pageName();

protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);

    QVBoxLayout* createVideoCardComponent(QWidget* parent, const QString& title, const QList<PromotionCardParams>& videoCardParams);

    ElaPromotionCard* createVideoPromotionCard(QWidget* parent, const PromotionCardParams& param);
    QList<ElaPromotionCard*> createVideoPromotionCard(QWidget* parent, const QList<PromotionCardParams>& params);

    ElaPromotionCard* createPromotionCard(QWidget* parent, const PromotionCardParams& param);
    ElaPromotionView* createPromotionView(QWidget* parent, const QList<PromotionCardParams>& params);
    ElaPromotionView* createPromotionView(QWidget* parent, const QList<ElaPromotionCard*>& promotionCards);

private:
    void InitializeUI();
    void InitializeData();
    void InitializeConnect();

    ElaMenu* createContextMenu(QWidget* parent);
    ElaMenu* _contextMenu;
};


#endif // PROMOTION_PAGE_H
