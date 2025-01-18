#ifndef KEYBIND_CONTROLLER_H
#define KEYBIND_CONTROLLER_H

#include <QCoreApplication>
#include <QTreeWidgetItem>
#include <QString>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Keybind_PageModel.h"
#include "Keybind_TableModel.h"
#include "Keybind_TreeModel.h"
#include "Structs.h"
#include "Enums.h"

class Keybind_Controller : public QObject
{
    Q_OBJECT
public:
    explicit Keybind_Controller(Keybind_PageModel* PageModel = nullptr,Keybind_TableModel* TableModel = nullptr, Keybind_TreeModel* TreeModel = nullptr,  QObject* parent = nullptr);
    ~Keybind_Controller();

signals:
    // [Other]
    // - 未来将分离为 Keybind_PageModel 类的信号
    void keyInfoUpdated(QString StandardName, QString Description, QString Name); // 按键信息被更新
    void funcInfoUpdated(QString Name, QString Description, QString Detail); // 功能信息被更新

public slots:
    // [EventSlot]
    // - PageEvent
    void saveConfig(); // 保存配置文件
    void writeConfigFile(); // 写入配置文件
    void replaceKeybind(); // 替换按键绑定
    // - TableEvent
    void selectKey(const QModelIndex& index);
    void hoverKey(const QModelIndex& index);
    // - TreeEvent
    void selectFunction(const QModelIndex& index);
    void hoverFunction(const QModelIndex& index);

    // [DirectCall]
    // - CallPageModel
    void updateKeyInfo(); // 辅助函数，通知 PageModel 更新按键信息
    //void updateKeyInfo(const QModelIndex& index);
    //void updateFuncInfo(QTreeWidgetItem* item, int column);
    // - CallTableModel
    void updateFunctionInfo(const MouseState& role); // 辅助函数，通知 PageModel 更新功能信息
    //void resetKeybindTableModelData(); // 从配置文件中更新所有数据
    //void updateKeybindTableRowData(); // 更新单行数据
    // - CallTreeModel
    // - CallOthers
    //QJsonObject getGameKeyLinkGameFunc();
    //void updateKeyID2KeyInfo();
    //void updateFuncID2FuncInfo();

    // [Helper]
    // - writeConfigFile()
    //void writeKeybindsToStream(QTextStream& out, const QJsonObject& keybindList); // 写入按键绑定到流

    // [Other]
    // - 未来将分离为 JsonFile_Proc 类的函数
    //QJsonObject readJsonObj(const QString& filePath);
    //QJsonObject readJsonObj(const QFileInfo& fileInfo);
    //QJsonObject readJsonObj(const QResource& resource);

public:

private:
    // [Init]
    void initData(); // 初始化数据
    void initConfigDir(); // 初始化配置文件目录
    void initConfigFile(); // 初始化配置文件


    static const QString _defaultString; // 默认字符串

    Keybind_PageModel* _keybindPageModel; // 按键绑定页面模型
    Keybind_TableModel* _keybindTableModel; // 按键绑定表模型
    Keybind_TreeModel* _keybindTreeModel; // 功能树模型

    QFileInfo _gameInfoOutputDir; // 模拟游戏目录
    QFileInfo _configInfoKeyIDLinkFuncID; // 按键ID到功能ID的配置文件
    QResource _configResKeyIDLinkFuncID; // 按键ID到功能ID的资源
    QResource _configResKeyID2GameKey; // 按键ID到游戏按键的资源
    QResource _configResKeyID2KeyInfo; // 按键ID到按键信息的资源
    QResource _configResFuncID2GameFunc; // 功能ID到游戏功能的资源
    QResource _configResFuncID2FuncInfo; // 功能ID到功能信息的资源
    // QFileInfo 使用 exisits() 方法判断文件是否存在
    // QResource 使用 isValid() 方法判断资源是否有效

    QModelIndex _selectedKeybindIndex;
    QModelIndex _hoveredKeybindIndex;
    QModelIndex _selectedFunctionIndex;
    QModelIndex _hoveredFunctionIndex;

    QJsonObject _objKeyID2KeyInfo; // 按键ID到按键信息的映射
    QJsonObject _objFuncID2FuncInfo; // 功能ID到功能信息的映射

    QJsonObject _objUnknowKeyID2KeyInfo; // 未知按键ID到按键信息的映射
    QJsonObject _objUnknowFuncID2FuncInfo; // 未知功能ID到功能信息的映射
};

#endif // KEYBIND_CONTROLLER_H
