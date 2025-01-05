#ifndef KEYBIND_PAGE_H
#define KEYBIND_PAGE_H

#include "Page_BasePage.h"

#include "ElaTableView.h"
#include "ElaTreeView.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"

#include "Ovr_ElaTableView_Hover.h"
#include "Keybind_TableModel.h"
#include "Keybind_Controller.h"

class ElaComboBox;
class KeyBind_Page : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit KeyBind_Page(QWidget* parent = nullptr);
    ~KeyBind_Page();

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

    Keybind_TableModel* _keybindTableModel;
    QModelIndex _selectedKeybindIndex; // 仅在表格刷新时更新
    QModelIndex _hoveredKeybindIndex; // 剩下几个未使用
    QModelIndex _selectedFunctionIndex;
    QModelIndex _hoveredFunctionIndex;

    Keybind_Controller* _keybindController;

    Ovr_ElaTableView_Hover* _keybindTableView;
    ElaTreeView* _functionTreeView;
    QWidget* _toolBarWidget;
    QWidget* _keybindWidget;
    QWidget* _keyFunctionEditWidget;
    QWidget* _functionSelectWidget;

    ElaPushButton* _saveButton;
    ElaPushButton* _writeButton;
    ElaPushButton* _replaceFunctionPushButton;

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


#endif // KEYBIND_PAGE_H
