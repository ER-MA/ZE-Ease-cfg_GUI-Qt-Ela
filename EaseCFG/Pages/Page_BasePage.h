#ifndef PAGE_BASE_PAGE_H
#define PAGE_BASE_PAGE_H

#include <ElaScrollPage.h>


class QVBoxLayout;
class Page_BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Page_BasePage(QWidget* parent = nullptr);
    ~Page_BasePage();

protected:
    void createCustomWidget(QString descriptionText);
};


#endif // PAGE_BASE_PAGE_H
