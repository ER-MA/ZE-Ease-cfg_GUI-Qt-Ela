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

#include "KeybindTree_Proc.h"
#include "KeybindTable_Model.h"
#include "T_TreeViewModel.h"
#include "Ovr_ElaTreeView.h"

#include "Page_KeyBind.h"

Page_KeyBind::Page_KeyBind(QWidget* parent)
    : Page_BasePage(parent)
{
    initUI();
    initData();
    initConnect();
};

Page_KeyBind::~Page_KeyBind()
{

};

void Page_KeyBind::initUI()
{
    setWindowTitle("Key Bind"); // 窗口标题
    //setTitleVisible(false); // 隐藏标题栏
    setContentsMargins(20, 20, 20, 7);

    createCustomWidget("你可以在这里为按键分配功能; 你还可以添加多套按键配置, 以便游戏内随时切换 (v0.9)");

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
}

void Page_KeyBind::createFunctionImagePreview() // [功能预览] ※
{

}

void Page_KeyBind::createFunctionTreeView() // [功能选择] ※
{
    T_TreeViewModel* treeModel = new T_TreeViewModel(this);
    QFile file(":/Resource/Data/FunctionTreeView.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QByteArray jsonData = file.readAll();  // 读取文件内容到QByteArray中
    file.close();
    const QByteArray& jsonDataRef = jsonData;  // 返回jsonData
    treeModel->loadJsonData(jsonDataRef);
    //QModelIndex index = treeModel->index(0, 0);
    //QModelIndex index0_0 = treeModel->index(0, 0, index);
    //QString title = (treeModel->data(index, Qt::DisplayRole)).toString();
    //QString title0_0 = (treeModel->data(index0_0, Qt::DisplayRole)).toString();
    //qDebug() << "treeModel_Index_Title:" << title;
    //qDebug() << "treeModel_Index0_0_Title:" << title0_0;
    _functionTreeView = new ElaTreeView(this);
    //Ovr_ElaTreeView* _functionTreeView = new Ovr_ElaTreeView(this);
    _functionTreeView->setModel(treeModel);
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
}

void Page_KeyBind::createFunctionSelectWidget() // [功能选择] 布局
{
    _functionSelectWidget = new QWidget(this);
    QVBoxLayout* functionSelectVLayout = new QVBoxLayout(_functionSelectWidget);
    functionSelectVLayout->setContentsMargins(0, 0, 0, 0);
    functionSelectVLayout->addWidget(_functionTreeView);
}

void Page_KeyBind::createKeyFunctionEditWidget() // [按键功能编辑] ※
{
    ElaText* selectedKeyTitleLable = new ElaText(this);
    selectedKeyTitleLable->setText("选中按键：");
    selectedKeyTitleLable->setTextPixelSize(15);
    ElaText* selectedKeyNameLable = new ElaText(this);
    selectedKeyNameLable->setText("Null");
    selectedKeyNameLable->setTextPixelSize(15);
    ElaText* selectedKeyIntroLable = new ElaText(this);
    selectedKeyIntroLable->setText("(等待选择按键)");
    selectedKeyIntroLable->setTextPixelSize(15);
    QWidget* selectedKeyWidget = new QWidget(this);
    QHBoxLayout* selectedKeyHLayout = new QHBoxLayout(selectedKeyWidget);
    selectedKeyHLayout->setContentsMargins(0, 0, 0, 0);
    selectedKeyHLayout->addWidget(selectedKeyTitleLable);
    selectedKeyHLayout->addWidget(selectedKeyNameLable);
    selectedKeyHLayout->addStretch();
    selectedKeyHLayout->addWidget(selectedKeyIntroLable);

    ElaText* currentFunctionTitleLable = new ElaText(this);
    currentFunctionTitleLable->setText("当前功能：");
    currentFunctionTitleLable->setTextPixelSize(15);
    ElaText* currentFunctionNameLable = new ElaText(this);
    currentFunctionNameLable->setText("Null");
    currentFunctionNameLable->setTextPixelSize(15);
    QWidget* currentFunctionWidget = new QWidget(this);
    QHBoxLayout* currentFunctionHLayout = new QHBoxLayout(currentFunctionWidget);
    currentFunctionHLayout->setContentsMargins(0, 0, 0, 0);
    currentFunctionHLayout->addWidget(currentFunctionTitleLable);
    currentFunctionHLayout->addWidget(currentFunctionNameLable);
    currentFunctionHLayout->addStretch();

    QWidget* selectKeybindWidget = new QWidget(this);
    QVBoxLayout* selectKeybindVLayout = new QVBoxLayout(selectKeybindWidget);
    selectKeybindVLayout->setContentsMargins(0, 0, 0, 0);
    selectKeybindVLayout->addWidget(selectedKeyWidget);
    selectKeybindVLayout->addWidget(currentFunctionWidget);


    ElaText* selectedFunctionLable = new ElaText(this);
    selectedFunctionLable->setText("选中功能：");
    selectedFunctionLable->setTextPixelSize(15);
    ElaText* mousePointFunctionLable = new ElaText(this);
    mousePointFunctionLable->setText("Null");
    mousePointFunctionLable->setTextPixelSize(15);
    ElaPushButton* replaceFunctionPushButton = new ElaPushButton("替换当前功能", this);

    QWidget* replaceFunctionWidget = new QWidget(this);
    QHBoxLayout* replaceFunctionHLayout = new QHBoxLayout(replaceFunctionWidget);
    replaceFunctionHLayout->setContentsMargins(0, 0, 0, 0);
    replaceFunctionHLayout->addWidget(selectedFunctionLable);
    replaceFunctionHLayout->addWidget(mousePointFunctionLable);
    replaceFunctionHLayout->addStretch();
    replaceFunctionHLayout->addWidget(replaceFunctionPushButton);


    ElaText* functionDetailsTitleLabel = new ElaText(this);
    functionDetailsTitleLabel->setText("Null");
    functionDetailsTitleLabel->setTextPixelSize(15);
    ElaText* functionDetailsIntroLabel = new ElaText(this);
    functionDetailsIntroLabel->setText("暂无简介");
    functionDetailsIntroLabel->setTextPixelSize(15);
    ElaText* functionDetailsNoteTitleLabel = new ElaText(this);
    functionDetailsNoteTitleLabel->setText("备注：");
    functionDetailsNoteTitleLabel->setTextPixelSize(15);
    ElaText* functionDetailsNoteLabel = new ElaText(this);
    functionDetailsNoteLabel->setText("暂无功能备注。");
    functionDetailsNoteLabel->setTextPixelSize(15);

    QWidget* functionDetailsWidget = new QWidget(this);
    QVBoxLayout* functionDetailsVLayout = new QVBoxLayout(functionDetailsWidget);
    functionDetailsVLayout->setContentsMargins(0, 0, 0, 0);
    functionDetailsVLayout->addWidget(functionDetailsTitleLabel);
    functionDetailsVLayout->addWidget(functionDetailsIntroLabel);
    functionDetailsVLayout->addWidget(functionDetailsNoteTitleLabel);
    functionDetailsVLayout->addWidget(functionDetailsNoteLabel);


    _keyFunctionEditWidget = new QWidget(this);
    QVBoxLayout* keyFunctionEditVLayout = new QVBoxLayout(_keyFunctionEditWidget);
    keyFunctionEditVLayout->setContentsMargins(0, 0, 0, 0);
    keyFunctionEditVLayout->addWidget(selectKeybindWidget);
    keyFunctionEditVLayout->addWidget(replaceFunctionWidget);
    keyFunctionEditVLayout->addWidget(functionDetailsWidget);
}

void Page_KeyBind::createKeybindTableView() // [按键绑定列表] ※
{
    _keybindTableView = new ElaTableView(this);
    _keybindTableView->setHeaderMargin(10);  // 设置表头边距
    KeybindTableModel* model = new KeybindTableModel(this);
    //Keybind_DataFetcher* fetcher = new Keybind_DataFetcher();
    //connect(fetcher, &Keybind_DataFetcher::dataFetched, model, &KeybindTableModel::fetchData);
    //fetcher->startFetch();
    _keybindTableView->setModel(model); // 设置模型
    _keybindTableView->horizontalHeader()->setStretchLastSection(true);  // 自动拉伸最后一列
    _keybindTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 自动拉伸所有列
    _keybindTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);  // 允许拖动调整列宽
    //_keybindTableView->horizontalHeader()->setMinimumSectionSize(60);  // 设置最小列宽
    //_keybindTableView->verticalHeader()->setMinimumSectionSize(46);  // 设置最小行高
    //_keybindTableView->verticalHeader()->setVisible(false);  // 隐藏左侧序列号
    _keybindTableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // 选择行为为行选择
    _keybindTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 大小策略为扩展
    //_keybindTableView->setShowGrid(true);  // 显示网格线
    connect(_keybindTableView, &ElaTableView::tableViewShow, this, [=]() {
        _keybindTableView->setColumnWidth(0, 100);
        _keybindTableView->setColumnWidth(1, 150);
    });
}

void Page_KeyBind::createKeybindWidget() // [按键绑定] 布局
{
    _keybindWidget = new QWidget(this);
    QHBoxLayout* keybindHLayout = new QHBoxLayout(_keybindWidget);
    keybindHLayout->setContentsMargins(0, 0, 0, 0);
    keybindHLayout->addWidget(_keybindTableView);
    keybindHLayout->addWidget(_keyFunctionEditWidget);
    keybindHLayout->addWidget(_functionSelectWidget);
}

void Page_KeyBind::createToolBarWidget() // [工具栏] ※
{
    ElaComboBox* modeComboBox = new ElaComboBox(this);
    QStringList comboList{
        "竞技模式",
        "跑图模式",
        "ZE 模式",
        "KZ 模式" };
    modeComboBox->addItems(comboList);

    _saveButton = new ElaPushButton(this);
    _saveButton->setText("保存");
    _writeButton = new ElaPushButton(this);
    _writeButton->setText("写入");

    _toolBarWidget = new QWidget(this);
    QHBoxLayout* toolBarHLayout = new QHBoxLayout(_toolBarWidget);
    toolBarHLayout->setContentsMargins(0, 0, 0, 0);
    toolBarHLayout->addWidget(modeComboBox);
    toolBarHLayout->addStretch();
    toolBarHLayout->addWidget(_saveButton);
    toolBarHLayout->addWidget(_writeButton);
}

void Page_KeyBind::setupCentralWidget() // [中心窗口] 布局
{
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("按键配置");
    this->addCentralWidget(centralWidget, true, false, 0);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget(testText);
    centerVLayout->addWidget(_toolBarWidget);
    centerVLayout->addWidget(_keybindWidget);
}

void Page_KeyBind::initData()
{
    _keybindProc = new KeybindTree_Proc(this);
};

void Page_KeyBind::initConnect()
{
    QString floderPath = QCoreApplication::applicationDirPath() + "/config/output";
    QFileInfo steamCfgDir(floderPath);
    connect(_writeButton, &ElaPushButton::clicked, this, [this, steamCfgDir]() {
        _keybindProc->writeConfigFile(steamCfgDir);
    });
};
