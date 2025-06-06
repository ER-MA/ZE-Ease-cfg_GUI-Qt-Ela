#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QListView>
#include <QMouseEvent>
#include <QHeaderView>

#include "ElaComboBox.h"
#include "ElaPushButton.h"
#include "ElaTableView.h"
#include "ElaTreeView.h"
#include "ElaText.h"
#include "ElaMessageBar.h"
#include "ElaImageCard.h"

#include "Ovr_ElaTreeView.h"
#include "Ovr_ElaTableView.h"
#include "ContextMenu_Base.h"

#include "Keybind_DB.h"
#include "Keybind_PageModel.h"
#include "Keybind_TableModel.h"
#include "Keybind_TreeModel.h"
#include "Keybind_Controller.h"

#include "Enums.h"

#include "T_TreeViewModel.h"

#include "Keybind_Page.h"

Keybind_Page::Keybind_Page(QWidget* parent)
    : Page_BasePage(parent)
{
    initUI();
    initData();
    initConnect();
};

Keybind_Page::~Keybind_Page()
{

};

const QString& Keybind_Page::pageName()
{
    static QString pageName("Keybind");
    return pageName;
}

void Keybind_Page::initUI()
{
    setWindowTitle("Key Bind"); // 窗口标题
    setContentsMargins(20, 20, 20, 7);

    // CentralWidget
    // ├── ToolBarWidget
    // ├── KeybindWidget
    // │   ├── KeybindTableView
    // │   ├── FunctionEditWidget
    // │   ├── FunctionSelectWidget
    // │       ├── FunctionTreeView
    // │       └── FunctionImagePreview

    createFunctionImagePreview();
    createFunctionTreeView();
    createFunctionSelectWidget();
    createKeyFunctionEditWidget();
    createKeybindTableView();
    createKeybindWidget();
    createToolBarWidget();
    setupCentralWidget();

    _contextMenu = createContextMenu(this);
}

void Keybind_Page::createFunctionImagePreview() // [功能预览] ※
{
    _functionImagePreview = new ElaImageCard(this);
    _functionImagePreview->setBorderRadius(10);
    _functionImagePreview->setIsPreserveAspectCrop(true);
    _functionImagePreview->setMaximumAspectRatio(qreal(16) / qreal(9));

    _functionImagePreview->setMinimumSize(320, 180);

    QImage image(":/Resource/Image/Card/dream.png");
    _functionImagePreview->setCardImage(image);
}

void Keybind_Page::createFunctionTreeView() // [功能选择] ※
{
    //T_TreeViewModel* treeModel = new T_TreeViewModel(this);
    //QFile file(":/Resource/Data/FunctionTreeView.json");
    //if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //    return;
    //}
    //QByteArray jsonData = file.readAll();  // 读取文件内容到QByteArray中
    //file.close();
    //const QByteArray& jsonDataRef = jsonData;  // 返回jsonData
    //treeModel->loadJsonData(jsonDataRef);
    // 
    //QModelIndex index = treeModel->index(0, 0);
    //QModelIndex index0_0 = treeModel->index(0, 0, index);
    //QString title = (treeModel->data(index, Qt::DisplayRole)).toString();
    //QString title0_0 = (treeModel->data(index0_0, Qt::DisplayRole)).toString();
    //qDebug() << "treeModel_Index_Title:" << title;
    //qDebug() << "treeModel_Index0_0_Title:" << title0_0;
    _functionTreeView = new Ovr_ElaTreeView(this);
    //Ovr_ElaTreeView* _functionTreeView = new Ovr_ElaTreeView(this);
    //_functionTreeView->setModel(treeModel);
    //_functionTreeView->setFixedHeight(450);
    //_functionTreeView->setUniformRowHeights(false);
    _functionTreeView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    _functionTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    _functionTreeView->setItemHeight(37);
    _functionTreeView->setHeaderMargin(10);
    _functionTreeView->setIndentation(23);
    QFont headerFont = _functionTreeView->header()->font();
    headerFont.setPixelSize(13); // 设置标题字体大小（全局默认字体大小为13）
    _functionTreeView->header()->setFont(headerFont); // 应用字体

    _functionTreeView->setMinimumSize(320, 180);
}

void Keybind_Page::createFunctionSelectWidget() // [功能选择] 布局
{
    _functionSelectWidget = new QWidget(this);
    QVBoxLayout* functionSelectVLayout = new QVBoxLayout(_functionSelectWidget);
    functionSelectVLayout->setContentsMargins(0, 0, 0, 0);
    functionSelectVLayout->addWidget(_functionTreeView);
    functionSelectVLayout->addWidget(_functionImagePreview);

    functionSelectVLayout->setStretchFactor(_functionTreeView, 2);
    functionSelectVLayout->setStretchFactor(_functionImagePreview, 1);
}

void Keybind_Page::createKeyFunctionEditWidget() // [按键功能编辑] ※
{
    _selectedKeyDescriptionLable = new ElaText(this);
    _selectedKeyDescriptionLable->setText("当前尚未选择按键");
    _selectedKeyDescriptionLable->setTextPixelSize(15);
    QWidget* selectedKeyDescriptionWidget = new QWidget(this);
    QHBoxLayout* selectedKeyDescriptionHLayout = new QHBoxLayout(selectedKeyDescriptionWidget);
    selectedKeyDescriptionHLayout->setContentsMargins(0, 0, 0, 0);
    selectedKeyDescriptionHLayout->addStretch();
    selectedKeyDescriptionHLayout->addWidget(_selectedKeyDescriptionLable);

    ElaText* selectedKeyTitleLable = new ElaText(this);
    selectedKeyTitleLable->setText("选中按键：");
    selectedKeyTitleLable->setTextPixelSize(15);
    _selectedKeyNameLable = new ElaText(this);
    _selectedKeyNameLable->setText("请选择按键");
    _selectedKeyNameLable->setTextPixelSize(15);
    _selectedKeyIntroLable = new ElaText(this);
    _selectedKeyIntroLable->setText("[左侧表格中]");
    _selectedKeyIntroLable->setTextPixelSize(15);
    QWidget* selectedKeyWidget = new QWidget(this);
    QHBoxLayout* selectedKeyHLayout = new QHBoxLayout(selectedKeyWidget);
    selectedKeyHLayout->setContentsMargins(0, 0, 0, 0);
    selectedKeyHLayout->addWidget(selectedKeyTitleLable);
    selectedKeyHLayout->addWidget(_selectedKeyNameLable);
    selectedKeyHLayout->addStretch();
    selectedKeyHLayout->addWidget(_selectedKeyIntroLable);

    ElaText* currentFunctionTitleLable = new ElaText(this);
    currentFunctionTitleLable->setText("当前功能：");
    currentFunctionTitleLable->setTextPixelSize(15);
    _currentFunctionNameLable = new ElaText(this);
    _currentFunctionNameLable->setText("未选择按键");
    _currentFunctionNameLable->setTextPixelSize(15);
    QWidget* currentFunctionWidget = new QWidget(this);
    QHBoxLayout* currentFunctionHLayout = new QHBoxLayout(currentFunctionWidget);
    currentFunctionHLayout->setContentsMargins(0, 0, 0, 0);
    currentFunctionHLayout->addWidget(currentFunctionTitleLable);
    currentFunctionHLayout->addWidget(_currentFunctionNameLable);
    currentFunctionHLayout->addStretch();

    QWidget* selectKeybindWidget = new QWidget(this);
    QVBoxLayout* selectKeybindVLayout = new QVBoxLayout(selectKeybindWidget);
    selectKeybindVLayout->setContentsMargins(0, 0, 0, 0);
    selectKeybindVLayout->addWidget(selectedKeyDescriptionWidget);
    selectKeybindVLayout->addWidget(selectedKeyWidget);
    selectKeybindVLayout->addWidget(currentFunctionWidget);


    ElaText* selectedFunctionLable = new ElaText(this);
    selectedFunctionLable->setText("选中功能：");
    selectedFunctionLable->setTextPixelSize(15);
    _mousePointFunctionLable = new ElaText(this);
    _mousePointFunctionLable->setText("请选择功能");
    _mousePointFunctionLable->setTextPixelSize(15);
    _replaceFunctionPushButton = new ElaPushButton("替换", this);

    QWidget* replaceFunctionWidget = new QWidget(this);
    QHBoxLayout* replaceFunctionHLayout = new QHBoxLayout(replaceFunctionWidget);
    replaceFunctionHLayout->setContentsMargins(0, 0, 0, 0);
    replaceFunctionHLayout->addWidget(selectedFunctionLable);
    replaceFunctionHLayout->addWidget(_mousePointFunctionLable);
    replaceFunctionHLayout->addStretch();
    replaceFunctionHLayout->addWidget(_replaceFunctionPushButton);


    _functionDetailsTitleLabel = new ElaText(this);
    _functionDetailsTitleLabel->setText("未选择功能");
    _functionDetailsTitleLabel->setTextPixelSize(15);
    _functionDetailsIntroLabel = new ElaText(this);
    _functionDetailsIntroLabel->setText("暂无简介");
    _functionDetailsIntroLabel->setTextPixelSize(15);
    _functionDetailsNoteTitleLabel = new ElaText(this);
    _functionDetailsNoteTitleLabel->setText("备注：");
    _functionDetailsNoteTitleLabel->setTextPixelSize(15);
    _functionDetailsNoteLabel = new ElaText(this);
    _functionDetailsNoteLabel->setText("暂无功能备注。");
    _functionDetailsNoteLabel->setTextPixelSize(15);

    QWidget* functionDetailsWidget = new QWidget(this);
    QVBoxLayout* functionDetailsVLayout = new QVBoxLayout(functionDetailsWidget);
    functionDetailsVLayout->setContentsMargins(0, 0, 0, 0);
    functionDetailsVLayout->addWidget(_functionDetailsTitleLabel);
    functionDetailsVLayout->addWidget(_functionDetailsIntroLabel);
    functionDetailsVLayout->addWidget(_functionDetailsNoteTitleLabel);
    functionDetailsVLayout->addWidget(_functionDetailsNoteLabel);


    _keyFunctionEditWidget = new QWidget(this);
    QVBoxLayout* keyFunctionEditVLayout = new QVBoxLayout(_keyFunctionEditWidget);
    keyFunctionEditVLayout->setContentsMargins(0, 0, 0, 0);
    keyFunctionEditVLayout->addWidget(selectKeybindWidget);
    keyFunctionEditVLayout->addWidget(replaceFunctionWidget);
    keyFunctionEditVLayout->addWidget(functionDetailsWidget);

    keyFunctionEditVLayout->setStretchFactor(selectKeybindWidget, 18);
    keyFunctionEditVLayout->setStretchFactor(replaceFunctionWidget, 18);
    keyFunctionEditVLayout->setStretchFactor(functionDetailsWidget, 64);
}

void Keybind_Page::createKeybindTableView() // [按键绑定列表] ※
{
    _keybindTableView = new Ovr_ElaTableView(this);

    // 表格配置
    _keybindTableView->setShowGrid(false);  // 显示网格线
    _keybindTableView->setAlternatingRowColors(false);  // 交替行背景色

    //_keybindTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 大小策略为扩展
    _keybindTableView->setHeaderMargin(10);  // 设置表头边距

    _keybindTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 编辑触发方式（禁止编辑）
    _keybindTableView->setWordWrap(true);  // 禁止换行
    _keybindTableView->setCornerButtonEnabled(false);  // 禁止右上角按钮
    _keybindTableView->setSortingEnabled(false);  // 允许排序
    _keybindTableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // 选择行为为行选择（选择整行）
    _keybindTableView->setSelectionMode(QAbstractItemView::SingleSelection);  // 选择模式为单选
}

void Keybind_Page::createKeybindWidget() // [按键绑定] 布局
{
    _keybindWidget = new QWidget(this);
    QHBoxLayout* keybindHLayout = new QHBoxLayout(_keybindWidget);
    keybindHLayout->setContentsMargins(0, 0, 0, 0);
    keybindHLayout->addWidget(_keybindTableView);
    keybindHLayout->addWidget(_keyFunctionEditWidget);
    keybindHLayout->addWidget(_functionSelectWidget);

    keybindHLayout->setStretchFactor(_keybindTableView, 1);
    keybindHLayout->setStretchFactor(_keyFunctionEditWidget, 1);
    keybindHLayout->setStretchFactor(_functionSelectWidget, 1);
}

void Keybind_Page::createToolBarWidget() // [工具栏] ※
{
    ElaComboBox* modeComboBox = new ElaComboBox(this);
    QStringList comboList{
        "竞技模式",
        "跑图模式",
        "ZE 模式",
        "KZ 模式" };
    modeComboBox->addItems(comboList);

    _testButton = new ElaToolButton(this);
    _testButton->setFixedSize(35, 35);
    _testButton->setElaIcon(ElaIconType::Bug);
    _undoButton = new ElaToolButton(this);
    _undoButton->setFixedSize(35, 35);
    _undoButton->setIsTransparent(false);
    _undoButton->setElaIcon(ElaIconType::Reply);
    _saveButton = new ElaPushButton(this);
    _saveButton->setText("保存");
    _writeButton = new ElaPushButton(this);
    _writeButton->setText("写入");

    _toolBarWidget = new QWidget(this);
    QHBoxLayout* toolBarHLayout = new QHBoxLayout(_toolBarWidget);
    toolBarHLayout->setContentsMargins(0, 0, 0, 0);
    toolBarHLayout->addWidget(modeComboBox);
    toolBarHLayout->addStretch();
    toolBarHLayout->addWidget(_testButton);
    toolBarHLayout->addWidget(_undoButton);
    toolBarHLayout->addWidget(_saveButton);
    toolBarHLayout->addWidget(_writeButton);
}

void Keybind_Page::setupCentralWidget() // [中心窗口] 布局
{
    setTitleVisible(true); // 标题栏是否可见
    createCustomWidget("你可以在这里为按键分配功能; 你还可以添加多套按键配置, 以便游戏内随时切换 (v0.9)");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("按键绑定");
    this->addCentralWidget(centralWidget, true, false, 0);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget(testText);
    centerVLayout->addWidget(_toolBarWidget);
    centerVLayout->addWidget(_keybindWidget);
}

void Keybind_Page::applyTableModelDepenedentSettings()
{
    // 在模型被应用前不能设置的参数
    // 表格样式配置
    _keybindTableView->setColumnWidth(0, 50);  // 设置列宽
    _keybindTableView->setColumnWidth(1, 100);  // 设置列宽
    // 水平表头配置
    QHeaderView* horHeader = _keybindTableView->horizontalHeader(); // 获取表头实例
    horHeader->setVisible(true);  // 显示表头
    horHeader->setHighlightSections(false);  // 表头高亮
    horHeader->setDefaultSectionSize(100);  // 设置默认列宽
    horHeader->setSectionResizeMode(0, QHeaderView::Interactive); // 如何调整列宽（列数，模式）
    horHeader->setSectionResizeMode(1, QHeaderView::Interactive); // 交互模式，允许用户调整列宽
    horHeader->setStretchLastSection(true);  // 自动拉伸填充最后一列

    horHeader->setSectionsMovable(false);  // 拖动表头以交换列位置
    horHeader->setSectionsClickable(false);  // 表头可点击（排序相关）
    // 垂直表头配置
    QHeaderView* verHeader = _keybindTableView->verticalHeader(); // 获取左侧序列号实例
    verHeader->setVisible(false);  // 隐藏左侧序列号
}

void Keybind_Page::applyTreeModelDepenedentSettings()
{
    // 在模型被应用前不能设置的参数
}

void Keybind_Page::initData()
{
    _keybindDB = new Keybind_DB(this);
    _keybindTableModel = new Keybind_TableModel(_keybindDB, this);
    _keybindPageModel = new Keybind_PageModel(_keybindDB, this);
    _keybindTreeModel = new Keybind_TreeModel(_keybindDB, this);
    _cfgFileProcessor = new Proc_CFGFile(_keybindDB, this);

    _keybindTableView->setModel(_keybindTableModel); // 设置表格模型
    applyTableModelDepenedentSettings(); // 进一步设置表格样式
    _functionTreeView->setModel(_keybindTreeModel); // 设置树形模型

    _functionTreeView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    _functionTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    _functionTreeView->setItemHeight(37); // ※
    _functionTreeView->setHeaderMargin(10);
    _functionTreeView->setIndentation(23);
    QFont headerFont = _functionTreeView->header()->font();
    headerFont.setPixelSize(13); // 设置标题字体大小（全局默认字体大小为13）
    _functionTreeView->header()->setFont(headerFont); // 应用字体
    _functionTreeView->setMinimumSize(320, 180);
    _functionTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑

    _keybindController = new Keybind_Controller(_keybindPageModel, _keybindTableModel, _keybindTreeModel, this);
};

void Keybind_Page::initConnect()
{
    //// 测试ElaMessageBar
    //connect(_saveButton, &ElaPushButton::clicked, this, [this]() {
    //    // 显示一个成功提示
    //    ElaMessageBar::success(ElaMessageBarType::TopRight, "成功", "操作成功完成！", 3000, this);
    //    // 显示一个警告提示
    //    ElaMessageBar::warning(ElaMessageBarType::TopLeft, "警告", "请注意，有潜在风险！", 3000, this);
    //    // 显示一个信息提示
    //    ElaMessageBar::information(ElaMessageBarType::BottomRight, "信息", "这是一条普通信息！", 3000, this);
    //    // 显示一个错误提示
    //    ElaMessageBar::error(ElaMessageBarType::BottomLeft, "错误", "操作失败，请重试！", 3000, this);
    //});



    // [EventSignal]

    // - PageEvevt
    connect(_testButton, &ElaPushButton::clicked, _keybindController, &Keybind_Controller::testOperation);
    connect(_undoButton, &ElaPushButton::clicked, _keybindController, &Keybind_Controller::undoOperation);
    connect(_saveButton, &ElaPushButton::clicked, _keybindController, &Keybind_Controller::saveConfig);
    connect(_writeButton, &ElaPushButton::clicked, _keybindController, &Keybind_Controller::writeConfigFile);
    connect(_replaceFunctionPushButton, &ElaPushButton::clicked, _keybindController, &Keybind_Controller::replaceKeybind);

    // TODO: 进一步重写鼠标事件以实现更好的交互体验
    // - TableEvent
    connect(_keybindTableView, &Ovr_ElaTableView::selectIndexChang, _keybindController, &Keybind_Controller::selectKey);
    connect(_keybindTableView, &Ovr_ElaTableView::hoverIndexChang, _keybindController, &Keybind_Controller::hoverKey);

    // - TreeEvent
    connect(_functionTreeView, &Ovr_ElaTreeView::selectIndexChang, _keybindController, &Keybind_Controller::selectFunction);
    connect(_functionTreeView, &Ovr_ElaTreeView::hoverIndexChang, _keybindController, &Keybind_Controller::hoverFunction);

    // [Signal-Slot]

    // - PageUI

    connect(_keybindPageModel, &Keybind_PageModel::keybindInfoUpdated, this, [this](QString keyAppellation, QString keyLabelContent, QString keyDescription, QString functionName) {
        _selectedKeyNameLable->setText(keyAppellation);
        _selectedKeyIntroLable->setText(keyLabelContent);
        _selectedKeyDescriptionLable->setText(keyDescription);
        _currentFunctionNameLable->setText(functionName);
    });

    connect(_keybindPageModel, &Keybind_PageModel::selectedFunctionInfoUpdated, this, [this](QString functionName) {
        _mousePointFunctionLable->setText(functionName);
    });

    connect(_keybindPageModel, &Keybind_PageModel::functionInfoUpdated, this, [this](QString functionName, QString functionDescription, QString functionDetail) {
        _functionDetailsTitleLabel->setText(functionName);
        _functionDetailsIntroLabel->setText(functionDescription);
        _functionDetailsNoteLabel->setText(functionDetail);
    });

    

    // - TableViewUI
    // 恢复 TableView 选中项
    connect(_keybindTableModel, &Keybind_TableModel::modelAboutToBeReset, this, [this]() {
        _selectedKeybindIndex = _keybindTableView->currentIndex();
    });
    connect(_keybindTableModel, &Keybind_TableModel::modelReset, this, [this]() {
        _keybindTableView->setCurrentIndex(_selectedKeybindIndex);
    });
    connect(_keybindTableModel, &Keybind_TableModel::selectedIndexChanged, _keybindTableView, &Ovr_ElaTableView::setCurrentIndex);
    connect(_keybindTableModel, &Keybind_TableModel::selectedIndexChanged, _keybindController, &Keybind_Controller::selectKey);

    // - TreeViewUI

};



ElaMenu* Keybind_Page::createContextMenu(QWidget* parent)
{
    // 右键菜单
    ContextMenu_Base* contextMenu = new ContextMenu_Base(parent);

    contextMenu->createCommonToolMenu(contextMenu);

    contextMenu->addSeparator();
    // QKeySequence key = QKeySequence(Qt::CTRL | Qt::Key_S);
    contextMenu->addElaIconAction(ElaIconType::BoxCheck, "保存", QKeySequence::Save);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateLeft, "撤销", QKeySequence::Undo);
    contextMenu->addElaIconAction(ElaIconType::ArrowRotateRight, "刷新", QKeySequence::Refresh);

    contextMenu->addElaIconAction(ElaIconType::Copy, "复制");

    contextMenu->addSeparator(); // --------

    contextMenu->createUnversalToolMenu(contextMenu);

    contextMenu->addSeparator(); // --------

    contextMenu->createNavigateMenu(contextMenu);

    return contextMenu;
}

void Keybind_Page::mouseReleaseEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::RightButton:
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        _contextMenu->popup(event->globalPosition().toPoint());
#else
        _contextMenu->popup(event->globalPos());
#endif
        break;
    }
    default:
    {
        break;
    }
    }
    ElaScrollPage::mouseReleaseEvent(event);
}
