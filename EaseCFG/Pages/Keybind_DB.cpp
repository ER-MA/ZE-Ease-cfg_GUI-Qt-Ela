#include "Keybind_DB.h"

#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QSqlError>



Keybind_DB::Keybind_DB(QObject *parent)
{
    initData();

    openDatabase(_csConfigDB, _csConfigDBFile);
}

Keybind_DB::~Keybind_DB()
{
    closeDatabase(_csConfigDB);
}


bool Keybind_DB::beginTransaction() {
    return true;
}
bool Keybind_DB::commitTransaction() {
    return true;
}
bool Keybind_DB::rollbackTransaction() {
    return true;
}


void Keybind_DB::initData()
{
    // 初始化数据库文件路径
    QString sysDBDir = QCoreApplication::applicationDirPath() + "/config/database";
    QString csConfigDB = sysDBDir + "/cs_config.db";
    QString srvCSConfigDB = sysDBDir + "/srv_cs_config.db"; // 暂时用本地数据库替代

    _csConfigDBFile.setFile(csConfigDB);
    _srvCSConfigDBFile.setFile(srvCSConfigDB);
}



QMap<QString, QString> Keybind_DB::getKeyBind()
{
    QMap<QString, QString> dataMap;
    QString sql = "SELECT * FROM key_bind";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        QString keyID = query.value("key_id").toString();
        QString functionID = query.value("function_id").toString();
        dataMap.insert(keyID, functionID);
    }

    return dataMap;
}

QHash<QString, QString> Keybind_DB::getKeyAppellation()
{
    QHash<QString, QString> dataHash;
    QString sql = "SELECT * FROM key_info";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        QString KeyID = query.value("key_id").toString();
        QString Appellation = query.value("real_appellation_cn").toString();
        dataHash.insert(KeyID, Appellation);
    }

    return dataHash;
}

QHash<QString, CSConfigStructs::KeyInfo> Keybind_DB::getKeyInfo()
{
    QHash<QString, CSConfigStructs::KeyInfo> dataHash;
    QString sql = "SELECT * FROM key_info";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        QString KeyID = query.value("key_id").toString();
        CSConfigStructs::KeyInfo item;
        item.Appellation = query.value("real_appellation_cn").toString();
        item.Description = query.value("real_description_cn").toString();
        item.LabelSymbol = query.value("real_lable_symbol").toString();
        item.LabelText = query.value("real_lable_text").toString();
        dataHash.insert(KeyID, item);
    }

    return dataHash;
}

QHash<QString, QString> Keybind_DB::getFunctionName()
{
    QHash<QString, QString> dataHash;
    QString sql = "SELECT * FROM function_info";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        QString FunctionID = query.value("function_id").toString();
        QString FunctionName = query.value("name_cn").toString();
        dataHash.insert(FunctionID, FunctionName);
    }

    return dataHash;
}

QHash<QString, CSConfigStructs::FunctionInfo> Keybind_DB::getFunctionInfo()
{
    QHash<QString, CSConfigStructs::FunctionInfo> dataHash;
    QString sql = "SELECT * FROM function_info";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        QString FunctionID = query.value("function_id").toString();
        CSConfigStructs::FunctionInfo item;
        item.Name = query.value("name_cn").toString();
        item.Description = query.value("description_cn").toString();
        item.Detail = query.value("detail_cn").toString();
        dataHash.insert(FunctionID, item);
    }

    return dataHash;
}

QList<TableStructs::KeybindItem> Keybind_DB::getKeyBindModelData()
{
    QList<TableStructs::KeybindItem> dataList;
    QString sql = "SELECT key_id, function_id FROM key_bind";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        TableStructs::KeybindItem item;
        item.KeyID = query.value("key_id").toString();
        item.FunctionID = query.value("function_id").toString();
        dataList.append(item);
    }

    return dataList;
}

QList<TableStructs::FunctionModelItem> Keybind_DB::getFunctionInfoModelData()
{
    QList<TableStructs::FunctionModelItem> dataList;
    QString sql = "SELECT function_id, name_cn, parent_id FROM function_info";
    QSqlQuery query(sql, _csConfigDB);

    QList<TableStructs::FunctionModelItem> functionList;

    while (query.next()) {
        TableStructs::FunctionModelItem item;
        item.Name = query.value("name_cn").toString();
        item.FunctionID = query.value("function_id").toString();
        item.ParentID = query.value("parent_id").toString();
        functionList.append(item);
    }
    
    return functionList;
}

bool Keybind_DB::replaceKeybind(const QString& key_id, const QString& function_id)
{
    qDebug() << "[Keybind_DB::replaceKeybind] replace keybind: " << key_id << ", " << function_id;

    // 检查数据库中的function_id是否与要替换的function_id相同
    QString checkSql = "SELECT function_id FROM key_bind WHERE key_id = :key_id";
    QSqlQuery checkQuery(_csConfigDB);
    checkQuery.prepare(checkSql);
    checkQuery.bindValue(":key_id", key_id);

    if (!checkQuery.exec() || !checkQuery.first()) {
        qWarning() << "[Keybind_DB::replaceKeybind] Failed to check existing functionid:" << checkQuery.lastError().text();
        return false;
    }

    QString existingFunctionID = checkQuery.value("function_id").toString();

    if (existingFunctionID == function_id) {
        qDebug() << "[Keybind_DB::replaceKeybind] No update needed for key_id:" << key_id;
        return true;
    }

    QString sql = "UPDATE key_bind SET function_id = :function_id WHERE key_id = :key_id";
    QSqlQuery query(_csConfigDB);
    query.prepare(sql);
    query.bindValue(":function_id", function_id);
    query.bindValue(":key_id", key_id);

    // 执行SQL语句
    if (!query.exec()) {
        qWarning() << "[Keybind_DB::replaceKeybind] Failed to replace keybind:" << query.lastError().text();
        return false;
    }

    // 检查是否有行被更新
    if (query.numRowsAffected() == 0) {
        qWarning() << "[Keybind_DB::replaceKeybind] No rows affected, key_id may not exist.";
        return false;
    }

    return true;
}



bool Keybind_DB::openDatabase(QSqlDatabase& DB, const QString& DBFile)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(DBFile);

    if (!DB.open()) {
        qDebug() << "[Keybind_DB::linkCSConfigDB] Failed to open database: " << DB.lastError().text();
        return false;
    }
}

bool Keybind_DB::openDatabase(QSqlDatabase& DB, const QFileInfo& DBFile)
{
    if (!openDatabase(DB, DBFile.absoluteFilePath()))
    {
        return false;
    }
}

bool Keybind_DB::closeDatabase(QSqlDatabase& DB)
{
    if (DB.isOpen())
    {
        DB.close();
        return true;
    }
    return false;
}
