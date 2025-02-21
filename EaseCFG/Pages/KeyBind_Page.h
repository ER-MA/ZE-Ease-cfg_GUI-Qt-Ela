#ifndef KEYBIND_PAGE_H
#define KEYBIND_PAGE_H

#include "Page_BasePage.h"

#include "ElaTableView.h"
#include "ElaTreeView.h"
#include "ElaToolButton.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"

#include "Ovr_ElaTableView.h"
#include "Ovr_ElaTreeView.h"

#include "Keybind_DB.h"
#include "Keybind_PageModel.h"
#include "Keybind_TableModel.h"
#include "Keybind_TreeModel.h"
#include "Keybind_Controller.h"

class ElaComboBox;
class Keybind_Page : public Page_BasePage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Keybind_Page(QWidget* parent = nullptr);
    ~Keybind_Page();

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

    Keybind_DB* _keybindDB;

    Keybind_PageModel* _keybindPageModel;

    Keybind_TableModel* _keybindTableModel;
    ElaText* _selectedKeyNameLable;
    ElaText* _selectedKeyIntroLable;
    ElaText* _selectedKeyDescriptionLable;
    ElaText* _currentFunctionNameLable;
    QModelIndex _selectedKeybindIndex; // 用于设置选中项
    QModelIndex _hoveredKeybindIndex; // 剩下几个未使用
    QModelIndex _selectedFunctionIndex;
    QModelIndex _hoveredFunctionIndex;

    Keybind_TreeModel* _keybindTreeModel;
    ElaText* _mousePointFunctionLable;
    ElaText* _functionDetailsTitleLabel;
    ElaText* _functionDetailsIntroLabel;
    ElaText* _functionDetailsNoteTitleLabel;
    ElaText* _functionDetailsNoteLabel;

    Ovr_ElaTableView* _keybindTableView;
    Ovr_ElaTreeView* _functionTreeView;
    QWidget* _toolBarWidget;
    QWidget* _keybindWidget;
    QWidget* _keyFunctionEditWidget;
    QWidget* _functionSelectWidget;

    ElaToolButton* _undoButton;
    ElaPushButton* _saveButton;
    ElaPushButton* _writeButton;
    ElaPushButton* _replaceFunctionPushButton;

    ElaImageCard* _functionImagePreview;

    Keybind_Controller* _keybindController;
};


#endif // KEYBIND_PAGE_H
