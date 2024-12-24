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
    KeybindTree_Proc* keybindProc = new KeybindTree_Proc(this);

    setWindowTitle("Key Bind");  // 窗口标题
    //setTitleVisible(false);  // 隐藏标题栏
    setContentsMargins(20, 20, 20, 7);

    createCustomWidget("你可以在这里为按键分配功能; 你还可以添加多套按键配置, 以便游戏内随时切换 (v0.9)");

    // testText(测试文本)
    //ElaText* testText = new ElaText("测试文本", this);


    // toolBarWidget(工具栏)
    ElaComboBox* modeComboBox = new ElaComboBox(this);
    QStringList comboList{
        "竞技模式",
        "跑图模式",
        "ZE 模式",
        "KZ 模式" };
    modeComboBox->addItems(comboList);

    ElaPushButton* saveButton = new ElaPushButton(this);
    saveButton->setText("保存");
    ElaPushButton* writeButton = new ElaPushButton(this);
    writeButton->setText("写入");
    QString floderPath = QCoreApplication::applicationDirPath() + "/config/output";
    QFileInfo steamCfgDir(floderPath);
    connect(writeButton, &ElaPushButton::clicked, this, [keybindProc, steamCfgDir]() {
        keybindProc->writeConfigFile(steamCfgDir);
    });

    QWidget* toolBarWidget = new QWidget(this);
    QHBoxLayout* toolBarHLayout = new QHBoxLayout(toolBarWidget);
    toolBarHLayout->setContentsMargins(0, 0, 0, 0);
    toolBarHLayout->addWidget(modeComboBox);
    toolBarHLayout->addStretch();
    toolBarHLayout->addWidget(saveButton);
    toolBarHLayout->addWidget(writeButton);


    // keybindWidget(按键绑定窗口)
    // keybindTableView(按键绑定表)
    ElaTableView* keybindTableView = new ElaTableView(this);
    keybindTableView->setHeaderMargin(10);  // 设置表头边距
    KeybindTableModel* model = new KeybindTableModel(this);
    //Keybind_DataFetcher* fetcher = new Keybind_DataFetcher();
    //connect(fetcher, &Keybind_DataFetcher::dataFetched, model, &KeybindTableModel::fetchData);
    //fetcher->startFetch();
    keybindTableView->setModel(model); // 设置模型
    keybindTableView->horizontalHeader()->setStretchLastSection(true);  // 自动拉伸最后一列
    keybindTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 自动拉伸所有列
    keybindTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);  // 允许拖动调整列宽
    //keybindTableView->horizontalHeader()->setMinimumSectionSize(60);  // 设置最小列宽
    //keybindTableView->verticalHeader()->setMinimumSectionSize(46);  // 设置最小行高
    //keybindTableView->verticalHeader()->setVisible(false);  // 隐藏左侧序列号
    keybindTableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // 选择行为为行选择
    keybindTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 大小策略为扩展
    //keybindTableView->setShowGrid(true);  // 显示网格线
    connect(keybindTableView, &ElaTableView::tableViewShow, this, [=]() {
        keybindTableView->setColumnWidth(0, 100);
        keybindTableView->setColumnWidth(1, 150);
    });


    // keyFunctionEditWidget(按键功能编辑窗口)
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


    QWidget* keyFunctionEditWidget = new QWidget(this);
    QVBoxLayout* keyFunctionEditVLayout = new QVBoxLayout(keyFunctionEditWidget);
    keyFunctionEditVLayout->setContentsMargins(0, 0, 0, 0);
    keyFunctionEditVLayout->addWidget(selectKeybindWidget);
    keyFunctionEditVLayout->addWidget(replaceFunctionWidget);
    keyFunctionEditVLayout->addWidget(functionDetailsWidget);

    // functionSelectWidget(功能选择窗口)
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
    ElaTreeView* functionTreeView = new ElaTreeView(this);
    //Ovr_ElaTreeView* functionTreeView = new Ovr_ElaTreeView(this);
    functionTreeView->setModel(treeModel);
    //functionTreeView->setFixedHeight(450);
    //functionTreeView->setUniformRowHeights(false);
    functionTreeView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    functionTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    functionTreeView->setItemHeight(37);
    functionTreeView->setHeaderMargin(10);
    functionTreeView->setIndentation(23);
    QFont headerFont = functionTreeView->header()->font();
    headerFont.setPixelSize(13); // 设置标题字体大小（全局默认字体大小为13）
    functionTreeView->header()->setFont(headerFont); // 应用字体


    QWidget* functionSelectWidget = new QWidget(this);
    QVBoxLayout* functionSelectVLayout = new QVBoxLayout(functionSelectWidget);
    functionSelectVLayout->setContentsMargins(0, 0, 0, 0);
    functionSelectVLayout->addWidget(functionTreeView);


    QWidget* keybindWidget = new QWidget(this);
    QHBoxLayout* keybindHLayout = new QHBoxLayout(keybindWidget);
    keybindHLayout->setContentsMargins(0, 0, 0, 0);
    keybindHLayout->addWidget(keybindTableView);
    keybindHLayout->addWidget(keyFunctionEditWidget);
    keybindHLayout->addWidget(functionSelectWidget);


    // centralWidget(中心窗口)
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("按键配置");
    this->addCentralWidget(centralWidget, true, false, 0);
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    //centerVLayout->addWidget(testText);
    centerVLayout->addWidget(toolBarWidget);
    centerVLayout->addWidget(keybindWidget);
};

void Page_KeyBind::initData()
{

};

void Page_KeyBind::initConnect()
{

};
