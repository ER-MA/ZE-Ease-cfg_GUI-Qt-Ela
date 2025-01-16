#ifndef KEYBIND_DB_H
#define KEYBIND_DB_H

#include <QObject>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QMap>
#include <QHash>

#include "Structs.h"



class Keybind_DB : public QObject
{
    Q_OBJECT
public:
    explicit Keybind_DB(QObject* parent = nullptr);
    ~Keybind_DB();

signals:
    void keyBindUpdated();
    void keyInfoUpdated();
    void functionInfoUpdated();

public:
    QMap<QString, QString> getKeyBind();

    QHash<QString, QString> getKeyAppellation();
    QHash<QString, CSConfigStructs::KeyInfo> getKeyInfo();

    QHash<QString, QString> getFunctionName();
    QHash<QString, CSConfigStructs::FunctionInfo> getFunctionInfo();

    QList<TableStructs::KeybindModelItem> getKeyBindModelData();
    QList<TableStructs::FunctionModelItem> getFunctionInfoModelData();



private:
    void initData();

    

    bool openDatabase(QSqlDatabase& DB, const QFileInfo& DBFile);
    bool openDatabase(QSqlDatabase& DB, const QString& DBFile);
    bool closeDatabase(QSqlDatabase& DB);

    QFileInfo _csConfigDBFile;
    QFileInfo _srvCSConfigDBFile;

    QSqlDatabase _csConfigDB;
    QSqlDatabase _srvCSConfigDB;
};



#endif // KEYBIND_DB_H
