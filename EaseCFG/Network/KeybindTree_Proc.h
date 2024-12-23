#ifndef KEYBINDTREE_PROC_H
#define KEYBINDTREE_PROC_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QResource>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDir>
#include <QFile>
#include <QCoreApplication>

class KeybindTree_Proc : public QObject
{
    Q_OBJECT
public:
    explicit KeybindTree_Proc(QObject *parent = nullptr);
    ~KeybindTree_Proc();

signals:

public slots:

    //void modifyKeybind(QString key, QString value); // 修改按键绑定
    //void overwriteKeybind(QJsonObject keybind); // 覆写按键绑定

private:
    void initConfigDir(); // 初始化配置文件目录
    void initConfigFile(); // 初始化配置文件

    QJsonObject readJsonObj(QString filePath); // 读取Json对象
    QJsonObject readKeybind(); // 读取按键绑定
    QJsonObject readQrcKeybind(); // 读取按键绑定
    QJsonObject readQrcKeyList(); // 读取按键列表
    QJsonObject readQrcFuncList(); // 读取功能列表;

    QString _configDirPath; // 配置文件目录路径
    QString _configKeyBindFilePath; // 按键绑定配置文件路径

    QString _configDirQrcPath; // 配置文件目录资源路径
    QString _configKeyBindFileQrcPath; // 按键绑定配置文件资源路径
    QString _configKeyListFileQrcPath; // 按键列表配置文件资源路径
    QString _configFuncListFileQrcPath; // 功能列表配置文件资源路径
};

#endif // KEYBINDTREE_PROC_H
