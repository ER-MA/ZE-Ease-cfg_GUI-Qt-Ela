#include "Page_BasePage.h"

#include <QHBoxLayout>
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

const QString& Page_BasePage::pageName()
{
    static QString pageName("BasePage");
    return pageName;
}

void Page_BasePage::createCustomWidget(QString descriptionText)
{
    // 顶部元素
    QWidget* customWidget = new QWidget(this);
    ElaText* subTitleText = new ElaText(this);
    subTitleText->setText(descriptionText);
    subTitleText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    subTitleText->setTextPixelSize(15);

    QVBoxLayout* topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(subTitleText);
    setCustomWidget(customWidget);
}
