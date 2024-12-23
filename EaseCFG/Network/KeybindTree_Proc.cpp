#include "KeybindTree_Proc.h"

KeybindTree_Proc::KeybindTree_Proc(QObject* parent) : QObject(parent)
{
    qDebug("[KeybindTree_Proc::KeybindTree_Proc] Constructor.");
    initConfigDir();
    initConfigFile();
    //// 测试函数readKeybind()的返回值
    //QJsonObject keybindObj = readKeybind();
    //QJsonDocument keybindDoc(keybindObj);
    //qDebug("[KeybindTree_Proc::KeybindTree_Proc] readKeybind() return value:\n%s", keybindDoc.toJson(QJsonDocument::Indented).data());
};

KeybindTree_Proc::~KeybindTree_Proc()
{

};

void KeybindTree_Proc::initConfigDir()
{
    _configDirPath = QCoreApplication::applicationDirPath() + "/config"; // 配置文件目录路径
    _configKeyBindFilePath = _configDirPath + "/KeyBind.json"; // 按键绑定配置文件路径

    _configDirQrcPath = ":/Resource/Data/Config/Keybind"; // 配置文件目录资源路径
    _configKeyBindFileQrcPath = _configDirQrcPath + "/KeyBind.json"; // 按键绑定配置文件资源路径
    _configKeyListFileQrcPath = _configDirQrcPath + "/KeyList.json"; // 按键列表配置文件资源路径
    _configFuncListFileQrcPath = _configDirQrcPath + "/FuncList.json"; // 功能列表配置文件资源路径

    // 检查config目录是否存在
    QDir configDir(_configDirPath);
    if (!configDir.exists()) {
        // 如果config目录不存在，则创建config目录
        if (!configDir.mkpath(".")) {
            // 如果无法创建config目录，则处理错误
            qDebug("[KeybindTree_Proc::initConfigDir] Unable to create config directory.");
        }
    }
}

void KeybindTree_Proc::initConfigFile()
{
    // TODO: 这里稍后修改为直接copy
    // 检查KeyBind.json文件是否存在
    QFile configKeyBindFile(_configKeyBindFilePath);
    if (!configKeyBindFile.exists()) {
        // 如果文件不存在，则从资源文件系统中读取KeyBind.json的内容
        QFile configKeyBindFileQrc(_configKeyBindFileQrcPath);
        if (configKeyBindFileQrc.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // 读取默认配置文件内容
            QByteArray configData = configKeyBindFileQrc.readAll();
            // 输出一下configData
            // qDebug("[KeybindTree_Proc::initConfigFile] Default KeyBind.json content:\n%s", configData.data());
            configKeyBindFileQrc.close();

            // 将默认配置文件内容写入到config目录下的KeyBind.json
            QFile newConfigKeyBindFile(_configKeyBindFilePath);
            if (newConfigKeyBindFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                newConfigKeyBindFile.write(configData);
                newConfigKeyBindFile.close();
            }
            else {
                // 如果无法写入文件，可以在这里处理错误
                qDebug("[KeybindTree_Proc::initConfigFile] Unable to write KeyBind.json file.");
            }
        }
        else {
            // 如果无法读取默认配置文件，可以在这里处理错误
            qDebug("[KeybindTree_Proc::initConfigFile] Unable to read Qrc KeyBind.json file.");
        }
    }
}

//添加以下.h中的函数
//private:
//QJsonObject readKeybind();
//QJsonObject readKeyList();
//QJsonObject readFuncList();


// 以下四个函数稍后删除，使用时直接调用readKeybind()即可
QJsonObject KeybindTree_Proc::readKeybind()
{
    QFile configKeyBindFile(_configKeyBindFilePath);
    if (!configKeyBindFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[KeybindTree_Proc::readKeybind] Unable to open KeyBind.json file.");
        return QJsonObject();
    }

    QByteArray jsonData = configKeyBindFile.readAll();
    configKeyBindFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug("[KeybindTree_Proc::readKeybind] JSON parse eror at offset %d: %s", jsonError.offset, jsonError.errorString().toUtf8().data());
        return QJsonObject();
    }

    QJsonObject keybindObj = jsonDoc.object();
    return keybindObj;
}

QJsonObject KeybindTree_Proc::readQrcKeybind()
{
    QFile configKeyBindFileQrc(_configKeyBindFileQrcPath);
    if (!configKeyBindFileQrc.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[KeybindTree_Proc::readQrcKeybind] Unable to open Qrc KeyBind.json file.");
        return QJsonObject();
    }

    QByteArray jsonData = configKeyBindFileQrc.readAll();
    configKeyBindFileQrc.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug("[KeybindTree_Proc::readQrcKeybind] JSON parse eror at offset %d: %s", jsonError.offset, jsonError.errorString().toUtf8().data());
        return QJsonObject();
    }

    QJsonObject keybindObj = jsonDoc.object();
    return keybindObj;
}

QJsonObject KeybindTree_Proc::readQrcKeyList()
{
    QFile configKeyListFile(_configKeyListFileQrcPath);
    if (!configKeyListFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[KeybindTree_Proc::readKeyList] Unable to open Qrc KeyList.json file.");
        return QJsonObject();
    }

    QByteArray jsonData = configKeyListFile.readAll();
    configKeyListFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug("[KeybindTree_Proc::readKeyList] JSON parse eror at offset %d: %s", jsonError.offset, jsonError.errorString().toUtf8().data());
        return QJsonObject();
    }

    QJsonObject keyListObj = jsonDoc.object();
    return keyListObj;
}

QJsonObject KeybindTree_Proc::readQrcFuncList()
{
    QFile configFuncListFile(_configFuncListFileQrcPath);
    if (!configFuncListFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[KeybindTree_Proc::readFuncList] Unable to open Qrc FuncList.json file.");
        return QJsonObject();
    }

    QByteArray jsonData = configFuncListFile.readAll();
    configFuncListFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug("[KeybindTree_Proc::readFuncList] JSON parse eror at offset %d: %s", jsonError.offset, jsonError.errorString().toUtf8().data());
        return QJsonObject();
    }

    QJsonObject funcListObj = jsonDoc.object();
    return funcListObj;
}
// 上面四个函数似乎能合并成一个函数，请帮我修改

QJsonObject KeybindTree_Proc::readJsonObj(QString filePath)
{
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug("[KeybindTree_Proc::readJsonObj] Unable to open %s file.", filePath.toUtf8().data());
        return QJsonObject();
    }

    QByteArray jsonData = configFile.readAll();
    configFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug("[KeybindTree_Proc::readJsonObj] JSON parse eror at offset %d: %s", jsonError.offset, jsonError.errorString().toUtf8().data());
        return QJsonObject();
    }

    QJsonObject jsonObj = jsonDoc.object();
    return jsonObj;
}
