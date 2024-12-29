#include "KeybindTree_Proc.h"

KeybindTree_Proc::KeybindTree_Proc(QObject* parent) : QObject(parent)
{
    initConfigDir();
    initConfigFile();

    // 打印Obj方式: qPrintable(QJsonDocument(readJsonObj(_configFuncListQrcFileRes)).toJson(QJsonDocument::Indented))
    QString path = ":/Resource/Data/Config/Keybind/Show_KeyInfoList.json";
};

KeybindTree_Proc::~KeybindTree_Proc()
{

};

void KeybindTree_Proc::initConfigDir()
{
    // 系统资源文件
    QString configDirPath = QCoreApplication::applicationDirPath() + "/config"; // 配置文件目录
    QString configKeyBindFilePath = configDirPath + "/KeyBind.json"; // 按键绑定配置文件（用户自定义）
    // Qrc系统资源文件
    QString configQrcDirPath = ":/Resource/Data/Config/Keybind"; // 配置文件目录
    QString configKeyBindFileQrcPath = configQrcDirPath + "/KeyBind.json"; // 按键绑定配置文件
    QString configKeyListFileQrcPath = configQrcDirPath + "/KeyList.json"; // 按键列表配置文件
    QString configFuncListFileQrcPath = configQrcDirPath + "/FuncList.json"; // 功能列表配置文件

    // 格式化文件路径
    _configKeyBindFileInfo.setFile(configKeyBindFilePath);
    _configKeyBindQrcFileRes.setFileName(configKeyBindFileQrcPath);
    _configKeyListQrcFileRes.setFileName(configKeyListFileQrcPath);
    _configFuncListQrcFileRes.setFileName(configFuncListFileQrcPath);
}

void KeybindTree_Proc::initConfigFile()
{
    // 检查配置文件是否存在
    if (!_configKeyBindFileInfo.exists()) {
        // 获取配置文件所在的目录
        QDir configDir = _configKeyBindFileInfo.dir();

        // 如果目录不存在，则尝试创建目录
        if (!configDir.exists() && !configDir.mkpath(".")) {
            // 处理目录创建失败的情况
            qWarning("[KeybindTree_Proc::initConfigFile] Failed to create config directory: %s", qPrintable(configDir.absolutePath()));
        }
        else {
            // 检查资源文件是否有效，并且复制资源到配置文件位置
            if (_configKeyBindQrcFileRes.isValid()) {
                QString sourcePath = _configKeyBindQrcFileRes.absoluteFilePath();
                QString targetPath = _configKeyBindFileInfo.absoluteFilePath();

                if (QFile::copy(sourcePath, targetPath)) {
                    // 设置新创建的配置文件的权限
                    QFile newConfigKeyBindFile(targetPath);
                    newConfigKeyBindFile.setPermissions(QFile::ReadUser | QFile::WriteUser);
                    qDebug("[KeybindTree_Proc::initConfigFile] Succeed to create new config file: %s", qPrintable(targetPath));
                }
                else {
                    // 处理文件复制失败的情况
                    qWarning("[KeybindTree_Proc::initConfigFile] Failed to copy file from %s to %s.", qPrintable(sourcePath), qPrintable(targetPath));
                }
            }
            else {
                // 处理资源文件无效的情况
                qWarning("[KeybindTree_Proc::initConfigFile] Invalid resource file: %s", qPrintable(_configKeyBindQrcFileRes.absoluteFilePath()));
            }
        }
    }
}

void KeybindTree_Proc::selectKey(QTreeWidgetItem* item, int column)
{

}
void KeybindTree_Proc::hoverKey(QTreeWidgetItem* item, int column)
{

}
void KeybindTree_Proc::selectFunc(QTreeWidgetItem* item, int column)
{

}
void KeybindTree_Proc::hoverFunc(QTreeWidgetItem* item, int column)
{

}

void KeybindTree_Proc::replaceKeybind(const QJsonObject& keybind)
{

}

void KeybindTree_Proc::saveConfig()
{

}

void KeybindTree_Proc::writeConfigFile(const QFileInfo& cfgDirInfo)
{
    // 检查配置目录是否存在
    if (!cfgDirInfo.exists() || !cfgDirInfo.isDir()) {
        qWarning("[KeybindTree_Proc::writeConfigFile] Config directory does not exist or is not a directory: %s", qPrintable(cfgDirInfo.absoluteFilePath()));
        return;
    }

    // 创建文件路径
    QString fileName = "keybinds.cfg";
    QString filePath = cfgDirInfo.absoluteFilePath() + "/" + fileName;
    qDebug("[KeybindTree_Proc::writeConfigFile] Generating keybind file at: %s", qPrintable(filePath));

    // 确保目录存在
    QDir dir(cfgDirInfo.absoluteFilePath());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning("[KeybindTree_Proc::writeConfigFile] Directory missing and unable to create: %s", qPrintable(cfgDirInfo.absoluteFilePath()));
            return;
        }
    }

    // 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("[KeybindTree_Proc::writeConfigFile] Unable to open file for writing: %s", qPrintable(filePath));
        return;
    }

    // 创建文本流
    QTextStream out(&file);

    // 生成并写入按键绑定
    writeKeybindsToStream(out, generateKeybindList());

    // 关闭文件
    file.close();
}

void KeybindTree_Proc::writeKeybindsToStream(QTextStream& out, const QJsonObject& keybindList)
{
    for (auto it = keybindList.constBegin(); it != keybindList.constEnd(); ++it) {
        QString key = it.key();
        QString function = it.value().toString();
        out << "bind " << key << " \"" << function << "\"" << "\n";
    }
}

QJsonObject KeybindTree_Proc::generateKeybindList()
{
    QJsonObject keyBindObj = readJsonObj(_configKeyBindFileInfo.absoluteFilePath());
    QJsonObject keyListObj = readJsonObj(_configKeyListQrcFileRes.absoluteFilePath());
    QJsonObject funcListObj = readJsonObj(_configFuncListQrcFileRes.absoluteFilePath());

    QJsonObject resultObj;

    // 遍历KeyBind.json中的每个键值对
    for (auto keyBindIter = keyBindObj.constBegin(); keyBindIter != keyBindObj.constEnd(); ++keyBindIter) {
        // 获取按键唯一标识符和功能唯一标识符
        QString keyId = keyBindIter.key();
        QString funcId = keyBindIter.value().toString();

        // 在KeyList.json中找到对应的游戏可识别的按键
        if (!keyListObj.contains(keyId)) {
            qWarning() << "[KeybindTree_Proc::generateKeybindList] Key ID not found in Qrc KeyList.json:" << keyId;
            continue; // 跳过未知的按键标识符
        }
        QString gameKey = keyListObj.value(keyId).toString();

        // 在FuncList.json中找到对应的游戏可识别的功能
        if (!funcListObj.contains(funcId)) {
            qWarning() << "[KeybindTree_Proc::generateKeybindList] Function ID not found in Qrc FuncList.json:" << funcId;
            continue; // 跳过未知的功能标识符
        }
        QString gameFunc = funcListObj.value(funcId).toString();

        // 添加到结果QJsonObject中
        resultObj.insert(gameKey, gameFunc);
    }

    // 返回新的QJsonObject
    return resultObj;
}

QJsonObject KeybindTree_Proc::readJsonObj(const QString& filePath)
{
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("[KeybindTree_Proc::readJsonObj] Unable to open file: %s", qPrintable(filePath));
        return QJsonObject();
    }

    QByteArray jsonData = configFile.readAll();
    configFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[KeybindTree_Proc::readJsonObj] JSON parse error at offset %d: %s", jsonError.offset, qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}

QJsonObject KeybindTree_Proc::readJsonObj(const QFileInfo& fileInfo)
{
    if (!fileInfo.exists()) {
        qWarning("[KeybindTree_Proc::readJsonObj] File does not exist: %s", qPrintable(fileInfo.absoluteFilePath()));
        return QJsonObject();
    }
    return readJsonObj(fileInfo.absoluteFilePath());
}

QJsonObject KeybindTree_Proc::readJsonObj(const QResource& qrcFileRes)
{
    if (!qrcFileRes.isValid()) {
        qWarning("[KeybindTree_Proc::readJsonObj] Resource is not valid: %s", qPrintable(qrcFileRes.absoluteFilePath()));
        return QJsonObject();
    }

    QByteArray jsonData;
    QResource::Compression compression = qrcFileRes.compressionAlgorithm();
    if (compression != QResource::NoCompression) {
        // 如果资源被压缩，使用适当的解压缩方法
        if (compression == QResource::ZlibCompression) {
            jsonData = qUncompress(qrcFileRes.data(), qrcFileRes.size());
        }
        else if (compression == QResource::ZstdCompression) {
            // 需要包含zstd库并链接到它
            // jsonData = ZSTD_decompress(qrcFileRes.data(), qrcFileRes.uncompressedSize());
            qWarning("[KeybindTree_Proc::readJsonObj] Zstd compression is not supported.");
            return QJsonObject();
        }
        else {
            qWarning("[KeybindTree_Proc::readJsonObj] Unknown compression algorithm.");
            return QJsonObject();
        }
    }
    else {
        // 如果资源未压缩，直接读取数据
        jsonData = QByteArray(reinterpret_cast<const char*>(qrcFileRes.data()), qrcFileRes.size());
    }

    if (jsonData.isEmpty()) {
        qWarning("[KeybindTree_Proc::readJsonObj] Resource data is empty.");
        return QJsonObject();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[KeybindTree_Proc::readJsonObj] JSON parse error: %s", qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}
