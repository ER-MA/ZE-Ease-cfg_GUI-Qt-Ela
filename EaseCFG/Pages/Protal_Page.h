#ifndef PROTAL_PAHE_H
#define PROTAL_PAHE_H

#include "Page_BasePage.h"


struct UrlCardParams {
    QString title;          // 标题
    QString subtitle;       // 副标题
    QString imagePath;      // 图片路径
    QString url;            // 链接
    QString tooltip;        // 悬浮提示
};


class Page_BasePage;
class ElaAcrylicUrlCard;
class Protal_Page : public Page_BasePage
{
    Q_OBJECT
public:
    explicit Protal_Page(QWidget* parent = nullptr);

protected:
    QList<ElaAcrylicUrlCard*> createUrlCards(QWidget* parent, const QList<UrlCardParams>& params);

private:
    void InitializeUI();
    void InitializeData();
    void InitializeConnect();
};


#endif // PROTAL_PAHE_H
