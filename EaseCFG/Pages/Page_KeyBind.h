#ifndef PAGE_KEYBIND_H
#define PAGE_KEYBIND_H

#include "Page_BasePage.h"

#include "ElaTableView.h"
#include "ElaTreeView.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"

#include "Ovr_ElaTableView_Hover.h"
#include "KeybindTable_Model.h"
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

    // UI创建
    void createFunctionImagePreview();
    void createFunctionTreeView();
    void createFunctionSelectWidget();
    void createKeyFunctionEditWidget();
    void createKeybindTableView();
    void createKeybindWidget();
    void createToolBarWidget();
    void setupCentralWidget();

    // 模型依赖设置
    void applyTableModelDepenedentSettings();
    void applyTreeModelDepenedentSettings();

    KeybindTable_Model* _keybindTableModel;
    QModelIndex _selectedKeybindIndex;
    QModelIndex _hoveredKeybindIndex;
    QModelIndex _selectedFunctionIndex;
    QModelIndex _hoveredFunctionIndex;

    KeybindTree_Proc* _keybindProc;

    Ovr_ElaTableView_Hover* _keybindTableView;
    ElaTreeView* _functionTreeView;
    QWidget* _toolBarWidget;
    QWidget* _keybindWidget;
    QWidget* _keyFunctionEditWidget;
    QWidget* _functionSelectWidget;

    ElaPushButton* _saveButton;
    ElaPushButton* _writeButton;

    ElaText* _selectedKeyNameLable;
    ElaText* _selectedKeyIntroLable;
    ElaText* _currentFunctionNameLable;
    ElaText* _mousePointFunctionLable;
    ElaText* _functionDetailsTitleLabel;
    ElaText* _functionDetailsIntroLabel;
    ElaText* _functionDetailsNoteTitleLabel;
    ElaText* _functionDetailsNoteLabel;

    ElaImageCard* _functionImagePreview;
};


#endif // PAGE_KEYBIND_H
