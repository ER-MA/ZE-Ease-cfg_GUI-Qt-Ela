#ifndef KEYBIND_PAGEMODEL_H
#define KEYBIND_PAGEMODEL_H

#include <QObject>
#include <QHash>

#include "Structs.h"
#include "Keybind_DB.h"

class Keybind_PageModel : public QObject
{
    Q_OBJECT
public:
    explicit Keybind_PageModel(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Keybind_PageModel();

    void updateKeybindInfo(const QString& keyID, const QString& functionID);
    void updateFunctionInfo(const QString& functionID);
signals:
    void keybindInfoUpdated(const QString& keyAppellation, const QString& keyLabelContent, const QString& keyDescription, const QString& functionName);
    void functionInfoUpdated(const QString& Name, const QString& Description, const QString& Detail);

public slots:

private:
    void initData();
    void initConnection();

    void updateKeyInfoFromDB();
    void updateFunctionInfoFromDB();

    Keybind_DB* _keybindDB;

    QHash<QString, CSConfigStructs::KeyInfo> _keyInfo;
    QHash<QString, CSConfigStructs::FunctionInfo> _functionInfo;

    QString _testText = "Hello World!";

};

#endif // KEYBIND_PAGEMODEL_H
