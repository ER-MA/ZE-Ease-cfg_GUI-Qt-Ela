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

QList<TableStructs::KeybindModelItem> Keybind_DB::getKeyBindModelData()
{
    QList<TableStructs::KeybindModelItem> dataList;
    QString sql =
        "SELECT "
        "    ki.real_appellation_cn, "
        "    fi.name_cn, "
        "    kb.key_id, "
        "    kb.function_id "
        "FROM "
        "    key_bind AS kb "
        "INNER JOIN "
        "    key_info AS ki ON kb.key_id = ki.key_id "
        "INNER JOIN "
        "    function_info AS fi ON kb.function_id = fi.function_id";
    QSqlQuery query(sql, _csConfigDB);

    while (query.next()) {
        TableStructs::KeybindModelItem item;
        item.Key = query.value(0).toString();
        item.Function = query.value(1).toString();
        item.KeyID = query.value(2).toString();
        item.FunctionID = query.value(3).toString();
        dataList.append(item);
    }

    return dataList;
}

QList<QVariantMap> Keybind_DB::getFunctionInfoModelData()
{
    QList<QVariantMap> dataList;
    QString sql = "SELECT function_id, name_cn, parent_id FROM function_info";
    QSqlQuery query(sql, _csConfigDB);

    QList<QVariantMap> functionList;
    while (query.next()) {
        QVariantMap functionData;
        functionData["function_id"] = query.value("function_id");
        functionData["name_cn"] = query.value("name_cn");
        functionData["parent_id"] = query.value("parent_id");
        functionList.append(functionData);
    }

    return functionList;
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
