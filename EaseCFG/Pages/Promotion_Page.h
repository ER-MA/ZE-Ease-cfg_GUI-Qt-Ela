#ifndef PROMOTION_PAGE_H
#define PROMOTION_PAGE_H

#include "Page_BasePage.h"


class Page_BasePage;
class Promotion_Page : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Promotion_Page(QWidget* parent = nullptr);

    static const QString& pageName();

protected:


private:
    void InitializeUI();
    void InitializeData();
    void InitializeConnect();
};


#endif // PROMOTION_PAGE_H
