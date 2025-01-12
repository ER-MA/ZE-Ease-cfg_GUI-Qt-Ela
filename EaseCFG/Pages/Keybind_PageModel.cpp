#include "Keybind_PageModel.h"



Keybind_PageModel::Keybind_PageModel(Keybind_DB *keybindDB, QObject *parent)
    : QObject(parent),
    _keybindDB(keybindDB)
{
    initData();
    initConnection();
}

Keybind_PageModel::~Keybind_PageModel()
{

}



void Keybind_PageModel::updateKeybindInfo(const QString& keyID, const QString& functionID)
{
    CSConfigStructs::KeyInfo keyInfo = _keyInfo.value(keyID);
    QString keyAppellation = keyInfo.Appellation;
    QString keyLabelContent = "[ ";
    if (keyInfo.LabelSymbol.isEmpty())
        keyLabelContent = keyLabelContent + keyInfo.LabelText + " ";
    if (keyInfo.LabelText.isEmpty())
        keyLabelContent = keyLabelContent + keyInfo.LabelSymbol + " ";
    keyLabelContent = keyLabelContent + "] ";
    QString keyDescription = keyInfo.Description;

    CSConfigStructs::FunctionInfo functionInfo = _functionInfo.value(functionID);
    QString functionName = functionInfo.Name;

    emit keybindInfoUpdated(keyAppellation, keyLabelContent, keyDescription, functionName);
}

void Keybind_PageModel::updateFunctionInfo(const QString& functionID)
{
    CSConfigStructs::FunctionInfo functionInfo = _functionInfo.value(functionID);
    QString functionName = functionInfo.Name;
    QString functionDescription = functionInfo.Description;
    QString functionDetail = functionInfo.Detail;

    emit functionInfoUpdated(functionName, functionDescription, functionDetail);
}



void Keybind_PageModel::updateKeyInfoFromDB()
{
    _keyInfo = _keybindDB->getKeyInfo();
}

void Keybind_PageModel::updateFunctionInfoFromDB()
{
    _functionInfo = _keybindDB->getFunctionInfo();
}

void Keybind_PageModel::initData()
{
    updateKeyInfoFromDB();
    updateFunctionInfoFromDB();
}

void Keybind_PageModel::initConnection()
{
    //connect(_keybindDB, &Keybind_DB::keyBindUpdated, this, &Keybind_PageModel::);
    connect(_keybindDB, &Keybind_DB::keyInfoUpdated, this, &Keybind_PageModel::updateKeyInfoFromDB);
    connect(_keybindDB, &Keybind_DB::functionInfoUpdated, this, &Keybind_PageModel::updateFunctionInfoFromDB);
}
