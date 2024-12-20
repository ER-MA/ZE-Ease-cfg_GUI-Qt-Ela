#ifndef PAGE_BASEPAGE_H
#define PAGE_BASEPAGE_H

#include <ElaScrollPage.h>

class QVBoxLayout;
class Page_BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Page_BasePage(QWidget* parent = nullptr);
    ~Page_BasePage();

private:
    QString subTitle;
    QString description;
    void setSubTitleText(QString subTitle);
    void setDescText(QString description);

protected:
    void createCustomWidget(QString description = "This is a Description");
    //virtual void paintEvent(QPaintEvent* event) override;
};

#endif // Page_BasePage_H
