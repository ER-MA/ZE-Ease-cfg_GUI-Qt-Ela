#ifndef PAGE_KEYBIND_H
#define PAGE_KEYBIND_H

#include "Page_BasePage.h"

#include "ElaTreeView.h"

class ElaComboBox;
class Page_KeyBind : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Page_KeyBind(QWidget* parent = nullptr);
    ~Page_KeyBind();

protected:


private:

};


#endif // PAGE_KEYBIND_H
