#include "Promotion_Page.h"

#include "Page_BasePage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


Promotion_Page::Promotion_Page(QWidget *parent) :
    Page_BasePage(parent)
{
    InitializeUI();
    InitializeData();
    InitializeConnect();
}

void Promotion_Page::InitializeUI()
{
    setWindowTitle("Promotion Page"); // 窗口标题
    setContentsMargins(20, 20, 20, 7);





    setTitleVisible(true); // 标题栏是否可见
    createCustomWidget("直播、视频分享；及社区活动推广");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("社区推广");
    this->addCentralWidget(centralWidget, true, true, 0);

    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget();
}

void Promotion_Page::InitializeData()
{

}

void Promotion_Page::InitializeConnect()
{

}
