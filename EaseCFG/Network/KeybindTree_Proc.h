#ifndef KEYBINDTREE_PROC_H
#define KEYBINDTREE_PROC_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QResource>
#

class KeybindTree_Proc : public QObject
{
    Q_OBJECT
public:
    // 修改一下，需要传入model
    //explicit KeybindTree_Proc(QObject* parent = nullptr, QTreeWidget* treeWidget = nullptr);
    explicit KeybindTree_Proc(QObject *parent = nullptr);
    ~KeybindTree_Proc();

signals:

public slots:

    //void modifyKeybind(QString key, QString value); // 修改按键绑定
    //void overwriteKeybind(QJsonObject keybind); // 覆写按键绑定

    void selectKey(QTreeWidgetItem* item, int column);
    void hoverKey(QTreeWidgetItem* item, int column);
    void selectFunc(QTreeWidgetItem* item, int column);
    void hoverFunc(QTreeWidgetItem* item, int column);

    void replaceKeybind(const QJsonObject& keybind); // 替换按键绑定

    void saveConfig(); // 保存配置文件
    void writeConfigFile(const QFileInfo& cfgDirInfo); // 写入配置文件

private:
    void initConfigDir(); // 初始化配置文件目录
    void initConfigFile(); // 初始化配置文件

    QJsonObject readJsonObj(const QString& filePath);
    QJsonObject readJsonObj(const QFileInfo& fileInfo);
    QJsonObject readJsonObj(const QResource& resource);
    QJsonObject generateKeybindList(); // 生成游戏按键绑定列表
    void writeKeybindsToStream(QTextStream& out, const QJsonObject& keybindList); // 写入按键绑定到流

    QFileInfo _configKeyBindFileInfo; // 按键绑定配置文件信息
    QResource _configKeyBindQrcFileRes; // 按键绑定配置文件资源
    QResource _configKeyListQrcFileRes; // 按键列表配置文件资源
    QResource _configFuncListQrcFileRes; // 功能列表配置文件资源

    // QFileInfo 使用 exisits() 方法判断文件是否存在
    // QResource 使用 isValid() 方法判断资源是否有效
};

#endif // KEYBINDTREE_PROC_H
