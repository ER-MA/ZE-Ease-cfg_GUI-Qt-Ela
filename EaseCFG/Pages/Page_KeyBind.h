#ifndef PAGE_KEYBIND_H
#define PAGE_KEYBIND_H

#include "Page_BasePage.h"

#include "ElaTableView.h"
#include "ElaTreeView.h"
#include "ElaPushButton.h"

#include "KeybindTree_Proc.h"

class ElaComboBox;
class Page_KeyBind : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Page_KeyBind(QWidget* parent = nullptr);
    ~Page_KeyBind();

protected:


private:
    void initUI();
    void initData();
    void initConnect();

    void createFunctionImagePreview();
    void createFunctionTreeView();
    void createFunctionSelectWidget();
    void createKeyFunctionEditWidget();
    void createKeybindTableView();
    void createKeybindWidget();
    void createToolBarWidget();
    void setupCentralWidget();

    KeybindTree_Proc* _keybindProc;

    ElaTableView* _keybindTableView;
    ElaTreeView* _functionTreeView;
    QWidget* _toolBarWidget;
    QWidget* _keybindWidget;
    QWidget* _keyFunctionEditWidget;
    QWidget* _functionSelectWidget;

    ElaPushButton* _saveButton;
    ElaPushButton* _writeButton;
};


#endif // PAGE_KEYBIND_H
