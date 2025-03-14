#ifndef PROTAL_PAHE_H
#define PROTAL_PAHE_H

#include "Page_BasePage.h"

#include <QString>
#include <QUrl>

struct UrlCardParams {
    QString title;          // 标题
    QString subtitle;       // 副标题
    QString imagePath;      // 图片路径
    QString url;            // 链接
    QString tooltip;        // 悬浮提示
};

// 批量创建PopularCard用的行为参数结构体（支持三种触发类型）
struct PopularCardParams {
    // 基础参数
    QString title;
    QString subtitle;
    QString interactiveTips;    // 初始按钮文本
    QString imagePath;
    // 卡片展开后
    QString detailedText;
    QString buttonText;
    QString floatImagePath;     // 浮动图标路径

    // 交互行为配置（使用 std::variant 存储多种类型）
    std::variant<
        std::function<void()>,  // 通用回调
        QUrl                    // 直接打开URL
    > action;
};
/* 通用回调使用格式：
[this]() {
    qDebug() << "执行自定义操作";
    Q_EMIT elaSceneNavigation();
}
*/


class Page_BasePage;
class ElaAcrylicUrlCard;
class ElaImageCard;
class ElaPopularCard;
class Protal_Page : public Page_BasePage
{
    Q_OBJECT
public:
    explicit Protal_Page(QWidget* parent = nullptr);
Q_SIGNALS:
    Q_SIGNAL void pageProtalNavigation();
    Q_SIGNAL void pagePromotionNavigation();
    Q_SIGNAL void pageServerListNavigation();
    Q_SIGNAL void pageKeyBindNavigation();
    Q_SIGNAL void pageSettingNavigation();

protected:
    QList<ElaAcrylicUrlCard*> createUrlCards(QWidget* parent, const QList<UrlCardParams>& params);
    QList<ElaPopularCard*> createPopularCards(QWidget* parent, const QList<PopularCardParams>& params);

private:
    void InitializeUI();
    void InitializeData();
    void InitializeConnect();

    ElaImageCard* createTopComponent(QWidget* parent);
    QVBoxLayout* createMiddleComponent(QWidget* parent);
};


#endif // PROTAL_PAHE_H
