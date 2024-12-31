#include "KeybindTree_Proc.h"

KeybindTree_Proc::KeybindTree_Proc(KeybindTable_Model* model, QObject* parent) :
    QObject(parent),
    _keybindTableModel(model)
{
    initConfigDir();
    initConfigFile();

    updateKeyID2KeyInfo();
    updateFuncID2FuncInfo();

    // 打印Obj方式1(中文会出现乱码): qPrintable(QJsonDocument(readJsonObj(_configResFuncID2GameFunc)).toJson(QJsonDocument::Indented))
    // 打印Obj方式2(中文不会出现乱码): qDebug() << QJsonDocument(readJsonObj(_configResFuncID2GameFunc)).toJson(QJsonDocument::Indented).data();

};

KeybindTree_Proc::~KeybindTree_Proc()
{

};

void KeybindTree_Proc::initConfigDir()
{
    // 系统资源文件
    QString sysDirConfig = QCoreApplication::applicationDirPath() + "/config"; // 系统资源文件目录
    QString sysPathKeyIDLinkFuncID = sysDirConfig + "/KeyBind.json";
    // Qrc系统资源文件
    QString qrcDirKeybindConfig = ":/Resource/Data/Config/Keybind"; // Qrc系统资源文件目录
    QString qrcPathKeyIDLinkFuncID = qrcDirKeybindConfig + "/KeyID_Link_FuncID.json"; // 按键ID对应的功能ID
    QString qrcPathKeyID2GameKey = qrcDirKeybindConfig + "/KeyID_To_GameKey.json"; // 按键ID到游戏按键
    QString qrcPathFuncID2GameFunc = qrcDirKeybindConfig + "/FuncID_To_GameFunc.json"; // 功能ID到游戏功能
    QString qrcPathKeyID2KeyInfo = qrcDirKeybindConfig + "/KeyID_To_KeyInfo.json"; // 按键ID到按键信息
    QString qrcPathFuncID2FuncInfo = qrcDirKeybindConfig + "/FuncID_To_FuncInfo.json"; // 功能ID到功能信息

    // 格式化文件路径
    _configInfoKeyIDLinkFuncID.setFile(sysPathKeyIDLinkFuncID);
    _configResKeyIDLinkFuncID.setFileName(qrcPathKeyIDLinkFuncID);
    _configResKeyID2GameKey.setFileName(qrcPathKeyID2GameKey);
    _configResFuncID2GameFunc.setFileName(qrcPathFuncID2GameFunc);
    _configResKeyID2KeyInfo.setFileName(qrcPathKeyID2KeyInfo);
    _configResFuncID2FuncInfo.setFileName(qrcPathFuncID2FuncInfo);
}

void KeybindTree_Proc::initConfigFile()
{
    // 检查配置文件是否存在
    if (!_configInfoKeyIDLinkFuncID.exists()) {
        // 获取配置文件所在的目录
        QDir configDir = _configInfoKeyIDLinkFuncID.dir();

        // 如果目录不存在，则尝试创建目录
        if (!configDir.exists() && !configDir.mkpath(".")) {
            // 处理目录创建失败的情况
            qWarning("[KeybindTree_Proc::initConfigFile] Failed to create config directory: %s", qPrintable(configDir.absolutePath()));
        }
        else {
            // 检查资源文件是否有效，并且复制资源到配置文件位置
            if (_configResKeyIDLinkFuncID.isValid()) {
                QString sourcePath = _configResKeyIDLinkFuncID.absoluteFilePath();
                QString targetPath = _configInfoKeyIDLinkFuncID.absoluteFilePath();

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
                qWarning("[KeybindTree_Proc::initConfigFile] Invalid resource file: %s", qPrintable(_configResKeyIDLinkFuncID.absoluteFilePath()));
            }
        }
    }
}

void KeybindTree_Proc::selectKey(const QModelIndex& index)
{
    if (!index.isValid()) {
        _selectedKeybindIndex = QModelIndex();
        emit keyInfoUpdated("Null", "Null", "Null");
        return;
    }

    _selectedKeybindIndex = index;
    updateKeyInfo(_selectedKeybindIndex);
}

void KeybindTree_Proc::hoverKey(const QModelIndex& index)
{
    if (!index.isValid()) { // 鼠标移出
        _hoveredKeybindIndex = QModelIndex();
        selectKey(_selectedKeybindIndex);
        return;
    }

    _hoveredKeybindIndex = index;
    updateKeyInfo(_hoveredKeybindIndex);
}
void KeybindTree_Proc::updateKeyInfo(const QModelIndex& index)
{

    QString keyID = _keybindTableModel->dataKeyID(index).toString();
    QString functionID = _keybindTableModel->dataFunctionID(index).toString();

    QString StandardName = "Null";
    QString Description = "Null";
    QString Name = "Null";

    const QJsonObject& keyInfo = _objKeyID2KeyInfo.value(keyID).toObject();
    if (!keyInfo.isEmpty()) {
        StandardName = keyInfo["StandardName"].toString();
        Description = keyInfo["Description"].toString();
    }
    else {
        qWarning() << "[KeybindTree_Proc::selectKey] Key ID not found in Qrc KeyID_To_KeyInfo.json:" << keyID;
    }

    const QJsonObject& funcInfo = _objFuncID2FuncInfo.value(functionID).toObject();
    if (!keyInfo.isEmpty()) {
        Name = funcInfo["Name"].toString();
    }
    else {
        qWarning() << "[KeybindTree_Proc::selectKey] Function ID not found in Qrc FuncID_To_FuncInfo.json:" << functionID;
    }

    emit keyInfoUpdated(StandardName, Description, Name);
}

void KeybindTree_Proc::selectFunc(QTreeWidgetItem* item, int column)
{

}
void KeybindTree_Proc::hoverFunc(QTreeWidgetItem* item, int column)
{

}
void KeybindTree_Proc::updateFuncInfo(QTreeWidgetItem* item, int column)
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

void KeybindTree_Proc::updateKeyID2KeyInfo()
{
    _objKeyID2KeyInfo = readJsonObj(_configResKeyID2KeyInfo.absoluteFilePath());
}

void KeybindTree_Proc::updateFuncID2FuncInfo()
{
    _objFuncID2FuncInfo = readJsonObj(_configResFuncID2FuncInfo.absoluteFilePath());
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
    QJsonObject keyBindObj = readJsonObj(_configInfoKeyIDLinkFuncID.absoluteFilePath());
    QJsonObject keyListObj = readJsonObj(_configResKeyID2GameKey.absoluteFilePath());
    QJsonObject funcListObj = readJsonObj(_configResFuncID2GameFunc.absoluteFilePath());

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
