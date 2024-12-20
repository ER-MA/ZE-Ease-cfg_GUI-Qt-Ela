#include "Page_BasePage.h"

#include <QHBoxLayout>
//#include <QPainter>
#include <QVBoxLayout>

#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToolButton.h"


Page_BasePage::Page_BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent)
        {
            update();
        }
    });
}

Page_BasePage::~Page_BasePage()
{
}

void Page_BasePage::createCustomWidget(QString description)
{
    // 顶部元素
    QWidget* customWidget = new QWidget(this);

    //ElaText* subTitleText = new ElaText(this);
    //subTitleText->setText(subTitle);
    //subTitleText->setTextPixelSize(35);

    ElaText* descText = new ElaText(this);
    descText->setText(description);
    descText->setTextInteractionFlags(Qt::TextSelectableByMouse);  // 允许鼠标选中文本
    descText->setTextPixelSize(15);

    QVBoxLayout* topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    //topLayout->addWidget(subTitleText);
    //topLayout->addSpacing(5);
    topLayout->addWidget(descText);

    setCustomWidget(customWidget);
}

//void Page_BasePage::paintEvent(QPaintEvent* event)
//{
//    if (!parent())
//    {
//        QPainter painter(this);
//        painter.save();
//        painter.setRenderHint(QPainter::Antialiasing);
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(ElaThemeColor(eTheme->getThemeMode(), WindowBaseStart));
//        painter.drawRect(rect());
//        painter.restore();
//    }
//    ElaScrollPage::paintEvent(event);
//}

void Page_BasePage::setSubTitleText(QString subTitle)
{
    if (Page_BasePage::subTitle == subTitle && !subTitle.isEmpty() && !subTitle.isNull())
        return;

    Page_BasePage::subTitle = subTitle;
}

void Page_BasePage::setDescText(QString description)
{
    if (Page_BasePage::description == description && !description.isEmpty() && !description.isNull())
        return;

    Page_BasePage::description = description;
}
