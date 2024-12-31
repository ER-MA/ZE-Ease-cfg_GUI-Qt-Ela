#ifndef KEYBINDTREE_PROC_H
#define KEYBINDTREE_PROC_H

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

#include "KeybindTable_Model.h"

class KeybindTree_Proc : public QObject
{
    Q_OBJECT
public:
    explicit KeybindTree_Proc(KeybindTable_Model* model = nullptr, QObject* parent = nullptr);
    ~KeybindTree_Proc();

signals:
    void keyInfoUpdated(QString StandardName, QString Description, QString Name); // 按键信息被更新
    void funcInfoUpdated(QString Name, QString Description, QString Detail); // 功能信息被更新

public slots:

    //void modifyKeybind(QString key, QString value); // 修改按键绑定
    //void overwriteKeybind(QJsonObject keybind); // 覆写按键绑定

    void selectKey(const QModelIndex& index);
    void hoverKey(const QModelIndex& index);
    void selectFunc(QTreeWidgetItem* item, int column);
    void hoverFunc(QTreeWidgetItem* item, int column);

    void replaceKeybind(const QJsonObject& keybind); // 替换按键绑定

    void saveConfig(); // 保存配置文件
    void writeConfigFile(const QFileInfo& cfgDirInfo); // 写入配置文件

    void updateKeyID2KeyInfo();
    void updateFuncID2FuncInfo();

private:
    void initConfigDir(); // 初始化配置文件目录
    void initConfigFile(); // 初始化配置文件

    void updateKeyInfo(const QModelIndex& index);
    void updateFuncInfo(QTreeWidgetItem* item, int column);

    KeybindTable_Model* _keybindTableModel; // 按键绑定表模型

    QJsonObject readJsonObj(const QString& filePath);
    QJsonObject readJsonObj(const QFileInfo& fileInfo);
    QJsonObject readJsonObj(const QResource& resource);
    QJsonObject generateKeybindList(); // 生成游戏按键绑定列表
    void writeKeybindsToStream(QTextStream& out, const QJsonObject& keybindList); // 写入按键绑定到流

    QFileInfo _configInfoKeyIDLinkFuncID; // 按键ID到功能ID的配置文件
    QResource _configResKeyIDLinkFuncID; // 按键ID到功能ID的资源
    QResource _configResKeyID2GameKey; // 按键ID到游戏按键的资源
    QResource _configResFuncID2GameFunc; // 功能ID到游戏功能的资源
    QResource _configResKeyID2KeyInfo; // 按键ID到按键信息的资源
    QResource _configResFuncID2FuncInfo; // 功能ID到功能信息的资源
    // QFileInfo 使用 exisits() 方法判断文件是否存在
    // QResource 使用 isValid() 方法判断资源是否有效

    QModelIndex _selectedKeybindIndex;
    QModelIndex _hoveredKeybindIndex;
    QModelIndex _selectedFunctionIndex;
    QModelIndex _hoveredFunctionIndex;

    QJsonObject _objKeyID2KeyInfo; // 按键ID到按键信息的映射
    QJsonObject _objFuncID2FuncInfo; // 功能ID到功能信息的映射
};

#endif // KEYBINDTREE_PROC_H
