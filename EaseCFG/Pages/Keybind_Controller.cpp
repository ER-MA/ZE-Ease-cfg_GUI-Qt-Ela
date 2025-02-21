#include "Keybind_Controller.h"

Keybind_Controller::Keybind_Controller(Keybind_PageModel* PageModel, Keybind_TableModel* TableModel, Keybind_TreeModel* TreeModel, QObject* parent)
    : QObject(parent),
    _keybindPageModel(PageModel),
    _keybindTableModel(TableModel),
    _keybindTreeModel(TreeModel)
{
    initData();
};

Keybind_Controller::~Keybind_Controller()
{

};



// [Init]

// - variables

const QString Keybind_Controller::_defaultString = "Default";

// - functions

void Keybind_Controller::initData()
{
    initConfigDir();
    initConfigFile();

}

void Keybind_Controller::initConfigDir()
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

    // 模拟游戏目录
    QString sysDirGameOutput = QCoreApplication::applicationDirPath() + "/config/output";
    _gameInfoOutputDir.setFile(sysDirGameOutput);
}

void Keybind_Controller::initConfigFile()
{
    // 检查配置文件是否存在
    if (!_configInfoKeyIDLinkFuncID.exists()) {
        // 获取配置文件所在的目录
        QDir configDir = _configInfoKeyIDLinkFuncID.dir();

        // 如果目录不存在，则尝试创建目录
        if (!configDir.exists() && !configDir.mkpath(".")) {
            // 处理目录创建失败的情况
            qWarning("[Keybind_Controller::initConfigFile] Failed to create config directory: %s", qPrintable(configDir.absolutePath()));
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
                    qDebug("[Keybind_Controller::initConfigFile] Succeed to create new config file: %s", qPrintable(targetPath));
                }
                else {
                    // 处理文件复制失败的情况
                    qWarning("[Keybind_Controller::initConfigFile] Failed to copy file from %s to %s.", qPrintable(sourcePath), qPrintable(targetPath));
                }
            }
            else {
                // 处理资源文件无效的情况
                qWarning("[Keybind_Controller::initConfigFile] Invalid resource file: %s", qPrintable(_configResKeyIDLinkFuncID.absoluteFilePath()));
            }
        }
    }
}



// [EventSlot]

// - PageEvent

/*
void Keybind_Controller::writeConfigFile()
{
    // 检查配置目录是否存在
    if (!_gameInfoOutputDir.exists() || !_gameInfoOutputDir.isDir()) {
        qWarning("[Keybind_Controller::writeConfigFile] Config directory does not exist or is not a directory: %s", qPrintable(_gameInfoOutputDir.absoluteFilePath()));
        return;
    }

    // 创建文件路径
    QString fileName = "keybinds.cfg";
    QString filePath = _gameInfoOutputDir.absoluteFilePath() + "/" + fileName;
    qDebug("[Keybind_Controller::writeConfigFile] Generating keybind file at: %s", qPrintable(filePath));

    // 确保目录存在
    QDir dir(_gameInfoOutputDir.absoluteFilePath());
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning("[Keybind_Controller::writeConfigFile] Directory missing and unable to create: %s", qPrintable(_gameInfoOutputDir.absoluteFilePath()));
            return;
        }
    }

    // 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("[Keybind_Controller::writeConfigFile] Unable to open file for writing: %s", qPrintable(filePath));
        return;
    }

    // 创建文本流
    QTextStream out(&file);

    // 生成并写入按键绑定
    writeKeybindsToStream(out, getGameKeyLinkGameFunc());

    // 关闭文件
    file.close();
}
*/

void Keybind_Controller::undoOperation()
{
    _keybindTableModel->undoReplaceKeybind();
}

void Keybind_Controller::saveConfig()
{
    _keybindTableModel->appllyReplaceKeybindToDB();
}

void Keybind_Controller::writeConfigFile()
{
    // 暂时用于测试函数
    _keybindTableModel->hasUnsavedReplaceKeybind();
}

void Keybind_Controller::replaceKeybind()
{
    QModelIndex keyIndex = _keybindTableModel->getSelectedIndex();
    QModelIndex funcIndex = _keybindTreeModel->getSelectedIndex();
    if (!keyIndex.isValid()) {
        qWarning("[Keybind_Controller::replaceKeybind] Invalid key index.");
        return;
    }
    if (!funcIndex.isValid()) {
        qWarning("[Keybind_Controller::replaceKeybind] Invalid function index.");
        return;
    }
    QString funcID = _keybindTreeModel->getFunctionID(funcIndex).toString();
    _keybindTableModel->replaceKeybind(keyIndex, funcID);
}

// - TableEvent

void Keybind_Controller::selectKey(const QModelIndex& index)
{
    _keybindTableModel->setSelectedIndex(index);
    updateKeyInfo();
}

void Keybind_Controller::hoverKey(const QModelIndex& index)
{
    _keybindTableModel->setHoveredIndex(index);
    updateKeyInfo();
}

void Keybind_Controller::updateKeyInfo()
{
    QModelIndex index = _keybindTableModel->getShowIndex();
    QString keyID = _keybindTableModel->getKeyID(index).toString();
    QString functionID = _keybindTableModel->getFunctionID(index).toString();
    _keybindPageModel->updateKeybindInfo(keyID, functionID);
}

// - TreeEvent

void Keybind_Controller::selectFunction(const QModelIndex& index)
{
    _keybindTreeModel->setSelectedIndex(index);
    updateFunctionInfo(MouseState::SelectRole);
}

void Keybind_Controller::hoverFunction(const QModelIndex& index)
{
    _keybindTreeModel->setHoveredIndex(index);
    updateFunctionInfo(MouseState::HoverRole);
}

void Keybind_Controller::updateFunctionInfo(const MouseState& role)
{
    if (role == MouseState::SelectRole) {
        QModelIndex index = _keybindTreeModel->getSelectedIndex();
        QString functionID = _keybindTreeModel->getFunctionID(index).toString();
        _keybindPageModel->updateSelectedFunctionInfo(functionID);
    }
    if (role == MouseState::HoverRole) {

    }

    QModelIndex index = _keybindTreeModel->getShowIndex();
    QString functionID = _keybindTreeModel->getFunctionID(index).toString();
    _keybindPageModel->updateFunctionInfo(functionID);
}




// [DirectCall]

// - CallPageModel

/*
void Keybind_Controller::updateKeyInfo(const QModelIndex& index)
{
    QString keyID = _keybindTableModel->getKeyID(index).toString();
    QString functionID = _keybindTableModel->getFunctionID(index).toString();

    QString StandardName = _defaultString;
    QString Description = _defaultString;
    QString Name = _defaultString;

    // keyInfo 查找
    // 使用find方法和迭代器来访问元素，只有当元素存在时才通过it.value()获取QJsonObject的引用
    // 避免在未找到functionID时进行不必要的对象复制。
    auto keyIt = _objKeyID2KeyInfo.find(keyID);
    if (keyIt != _objKeyID2KeyInfo.end()) {
        const QJsonObject& keyInfo = keyIt.value().toObject();
        StandardName = keyInfo["StandardName"].toString(_defaultString);
        Description = keyInfo["Description"].toString(_defaultString);
    }
    else {
        qWarning() << "[Keybind_Controller::selectKey] Unknown key ID: " << keyID;
        StandardName = _objUnknowKeyID2KeyInfo["StandardName"].toString(_defaultString);
        Description = _objUnknowKeyID2KeyInfo["Description"].toString(_defaultString);
    }

    // funcInfo 查找
    auto funcIt = _objFuncID2FuncInfo.find(functionID);
    if (funcIt != _objFuncID2FuncInfo.end()) {
        const QJsonObject& funcInfo = funcIt.value().toObject();
        Name = funcInfo["Name"].toString(_defaultString);
    }
    else {
        qWarning() << "[Keybind_Controller::selectKey] Unknown function ID: " << functionID;
        Name = _objUnknowFuncID2FuncInfo["Name"].toString(_defaultString);
    }

    emit keyInfoUpdated(StandardName, Description, Name);
}

void Keybind_Controller::updateFuncInfo(QTreeWidgetItem* item, int column)
{

}
*/

// - CallTableModel

/*
void Keybind_Controller::resetKeybindTableModelData()
{
    QList<TableStructs::KeybindModelItem> _modelData;

    QJsonObject keyBindObj = readJsonObj(_configInfoKeyIDLinkFuncID.absoluteFilePath());
    if (keyBindObj.isEmpty()) {
        return;
    }

    // 遍历KeyBind.json中的每个键值对
    for (auto keyBindIter = keyBindObj.constBegin(); keyBindIter != keyBindObj.constEnd(); ++keyBindIter)
    {
        // 获取按键唯一标识符和功能唯一标识符
        QString keyId = keyBindIter.key();
        QString funcId = keyBindIter.value().toString();

        TableStructs::KeybindModelItem item;
        item.KeyID = keyId;
        item.FunctionID = funcId;

        // 在_objKeyID2KeyInfo中找到对应的按键信息
        auto keyInfoIt = _objKeyID2KeyInfo.find(keyId);
        if (keyInfoIt != _objKeyID2KeyInfo.end()) {
            const QJsonObject& keyInfo = keyInfoIt.value().toObject();
            item.Key = keyInfo["Abbreviation"].toString(_defaultString);
        }
        else {
            qWarning() << "[Keybind_Controller::resetKeybindTableModelData] Key ID not found in Qrc KeyID_To_KeyInfo.json:" << keyId;
            item.Key = _objUnknowKeyID2KeyInfo["Abbreviation"].toString(_defaultString);
        }
        // 在_objFuncID2FuncInfo中找到对应的功能信息
        auto funcInfoIt = _objFuncID2FuncInfo.find(funcId);
        if (funcInfoIt != _objFuncID2FuncInfo.end()) {
            const QJsonObject& funcInfo = funcInfoIt.value().toObject();
            item.Function = funcInfo["Name"].toString(_defaultString);
        }
        else {
            qWarning() << "[Keybind_Controller::resetKeybindTableModelData] Function ID not found in Qrc FuncID_To_FuncInfo.json:" << funcId;
            item.Function = _objUnknowFuncID2FuncInfo["Name"].toString(_defaultString);
        }

        _modelData.append(item);
    }

    _keybindTableModel->setModelData(_modelData);
}
*/

/*
void Keybind_Controller::updateKeybindTableRowData()
{

}
*/

// - CallTreeModel

// - CallOthers

/*
QJsonObject Keybind_Controller::getGameKeyLinkGameFunc()
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
            qWarning() << "[Keybind_Controller::getGameKeyLinkGameFunc] Key ID not found in Qrc KeyList.json:" << keyId;
            continue; // 跳过未知的按键标识符
        }
        QString gameKey = keyListObj.value(keyId).toString();

        // 在FuncList.json中找到对应的游戏可识别的功能
        if (!funcListObj.contains(funcId)) {
            qWarning() << "[Keybind_Controller::getGameKeyLinkGameFunc] Function ID not found in Qrc FuncList.json:" << funcId;
            continue; // 跳过未知的功能标识符
        }
        QString gameFunc = funcListObj.value(funcId).toString();

        // 添加到结果QJsonObject中
        resultObj.insert(gameKey, gameFunc);
    }

    // 返回新的QJsonObject
    return resultObj;
}
*/

/*
void Keybind_Controller::updateKeyID2KeyInfo()
{
    _objKeyID2KeyInfo = readJsonObj(_configResKeyID2KeyInfo.absoluteFilePath());

    auto keyInfoIt = _objKeyID2KeyInfo.find("unknow");
    if (keyInfoIt != _objKeyID2KeyInfo.end()) {
        _objUnknowKeyID2KeyInfo = keyInfoIt.value().toObject();
    }
    else {
        qWarning() << "[Keybind_Controller::updateKeyID2KeyInfo] UnDefined key ID:\"unknown\"";
    }
}
*/

/*
void Keybind_Controller::updateFuncID2FuncInfo()
{
    _objFuncID2FuncInfo = readJsonObj(_configResFuncID2FuncInfo.absoluteFilePath());

    auto funcInfoIt = _objFuncID2FuncInfo.find("unknow");
    if (funcInfoIt != _objFuncID2FuncInfo.end()) {
        _objUnknowFuncID2FuncInfo = funcInfoIt.value().toObject();
    }
    else {
        qWarning() << "[Keybind_Controller::updateFuncID2FuncInfo] UnDefined function ID:\"unknown\"";
    }
}
*/



// [Helper]

// - writeConfigFile()

/*
void Keybind_Controller::writeKeybindsToStream(QTextStream& out, const QJsonObject& keybindList)
{
    for (auto it = keybindList.constBegin(); it != keybindList.constEnd(); ++it) {
        QString key = it.key();
        QString function = it.value().toString();
        out << "bind " << key << " \"" << function << "\"" << "\n";
    }
}
*/



// [Other]

// - 未来将分离为 JsonFile_Proc 类的函数

/*
QJsonObject Keybind_Controller::readJsonObj(const QString& filePath)
{
    QFile configFile(filePath);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("[Keybind_Controller::readJsonObj] Unable to open file: %s", qPrintable(filePath));
        return QJsonObject();
    }

    QByteArray jsonData = configFile.readAll();
    configFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[Keybind_Controller::readJsonObj] JSON parse error at offset %d: %s", jsonError.offset, qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}
QJsonObject Keybind_Controller::readJsonObj(const QFileInfo& fileInfo)
{
    if (!fileInfo.exists()) {
        qWarning("[Keybind_Controller::readJsonObj] File does not exist: %s", qPrintable(fileInfo.absoluteFilePath()));
        return QJsonObject();
    }
    return readJsonObj(fileInfo.absoluteFilePath());
}
QJsonObject Keybind_Controller::readJsonObj(const QResource& qrcFileRes)
{
    if (!qrcFileRes.isValid()) {
        qWarning("[Keybind_Controller::readJsonObj] Resource is not valid: %s", qPrintable(qrcFileRes.absoluteFilePath()));
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
            qWarning("[Keybind_Controller::readJsonObj] Zstd compression is not supported.");
            return QJsonObject();
        }
        else {
            qWarning("[Keybind_Controller::readJsonObj] Unknown compression algorithm.");
            return QJsonObject();
        }
    }
    else {
        // 如果资源未压缩，直接读取数据
        jsonData = QByteArray(reinterpret_cast<const char*>(qrcFileRes.data()), qrcFileRes.size());
    }

    if (jsonData.isEmpty()) {
        qWarning("[Keybind_Controller::readJsonObj] Resource data is empty.");
        return QJsonObject();
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qWarning("[Keybind_Controller::readJsonObj] JSON parse error: %s", qPrintable(jsonError.errorString()));
        return QJsonObject();
    }

    return jsonDoc.object();
}
*/

// - 未来将分离为 Keybind_PageModel 类的信号

// void keyInfoUpdated(QString StandardName, QString Description, QString Name); // 按键信息被更新

// void funcInfoUpdated(QString Name, QString Description, QString Detail); // 功能信息被更新
