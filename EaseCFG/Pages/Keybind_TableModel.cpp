#include "Keybind_TableModel.h"

#include <QTimer>

Keybind_TableModel::Keybind_TableModel(Keybind_DB* keybindDB, QObject* parent)
    : QAbstractTableModel(parent),
    _keybindDB(keybindDB)
{
    initModelData();
    initHeaderData();
    initConnection();

    updateKeyAppellationHashFromDB();
    updateFunctionNameHashFromDB();
    updateModelData();
}

Keybind_TableModel::~Keybind_TableModel()
{
    _modelData.clear();
}

// ovwerride

// [ItemData]

bool Keybind_TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || index.row() >= rowCount() || index.column() >= columnCount()) {
        return false;
    }
    if (role == Qt::EditRole) {
        switch (index.column()) {
        case 0: _modelData[index.row()].KeyID = value.toString(); break;
        case 1: _modelData[index.row()].FunctionID = value.toString(); break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant Keybind_TableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= rowCount() || index.column() >= columnCount()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return _keyAppellationHash.value(_modelData.at(index.row()).KeyID);
        case 1: return _functionNameHash.value(_modelData.at(index.row()).FunctionID);
        }
    }
    return QVariant();
}

// [HeaderData]

bool Keybind_TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) {
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (section >= 0 && section < _horHeaderData.count()) {
                _horHeaderData[section] = value.toString();
                emit headerDataChanged(orientation, section, section);
                return true;
            }
        }
    } else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole) {
            if (section >= 0 && section < _verHeaderData.count()) {
                _verHeaderData[section] = value.toString();
                emit headerDataChanged(orientation, section, section);
                return true;
            }
        }
    }
    return false;
}

QVariant Keybind_TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            if (section >= 0 && section < _horHeaderData.count()) {
            return _horHeaderData.at(section);
            }
        }
    } else if (orientation == Qt::Vertical) {
        if (role == Qt::DisplayRole) {
            if (section >= 0 && section < _verHeaderData.count()) {
                return _verHeaderData.at(section);
            }
        }
    }
    return QVariant();
}

// [Model]

int Keybind_TableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return _modelData.count();
}

int Keybind_TableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return 2;
}

// custom functions

// [ModelData]

void Keybind_TableModel::setModelData(const QList<TableStructs::KeybindItem>& datas) {
    beginResetModel();
    _modelData = datas;
    endResetModel();
}

QList<TableStructs::KeybindItem> Keybind_TableModel::getModelData() const
{
    return _modelData;
}

// [RowData]

bool Keybind_TableModel::setRowData(int row, const TableStructs::KeybindItem& newData) {
    if (row < 0 || row >= rowCount()) {
        return false;
    }
    _modelData[row] = newData;
    emit dataChanged(index(row, 0), index(row, columnCount() - 1));
    return true;
}

TableStructs::KeybindItem Keybind_TableModel::getRowData(int row) const
{
    if (row < 0 || row >= rowCount()) {
        return TableStructs::KeybindItem();
    }
    return _modelData.at(row);
}

QVariant Keybind_TableModel::getKeyID(const QModelIndex& index) {
    if (!index.isValid() || index.row() >= rowCount() || index.column() >= columnCount()) {
        return QVariant();
    }
    return _modelData.at(index.row()).KeyID;
}

QVariant Keybind_TableModel::getFunctionID(const QModelIndex& index) {
    if (!index.isValid() || index.row() >= rowCount() || index.column() >= columnCount()) {
        return QVariant();
    }
    return _modelData.at(index.row()).FunctionID;
}

// [Index]

QModelIndex Keybind_TableModel::getIndexByKeyID(const QString& keyID) const
{
    for (int i = 0; i < rowCount(); i++) {
        if (_modelData.at(i).KeyID == keyID) {
            return index(i, 0);
        }
    }
    return QModelIndex();
}

QList<QModelIndex> Keybind_TableModel::getIndexByFunctionID(const QString& functionID) const
{
    QList<QModelIndex> indexes;
    for (int i = 0; i < rowCount(); i++) {
        if (_modelData.at(i).FunctionID == functionID) {
            indexes.append(index(i, 1));
        }
    }
    return indexes;
}

// [init]

void Keybind_TableModel::initModelData() {
    // 初始化数据
    _modelData.clear();
    _modelData.append(TableStructs::KeybindItem{ "等待", "等待" });
    _modelData.append(TableStructs::KeybindItem{ "加载", "加载" });
    _modelData.append(TableStructs::KeybindItem{ "...", "..." });
}

void Keybind_TableModel::initHeaderData()
{
    // 水平表头
    _horHeaderData.clear();
    _horHeaderData.append("按键");
    _horHeaderData.append("功能");

    // 垂直表头
    _verHeaderData.clear();
    for (int i = 0; i < rowCount(); i++) {
        _verHeaderData.append(QString::number(i + 1));
    }
}

void Keybind_TableModel::initConnection() const
{
    //connect(_keybindDB, &Keybind_DB::keyBindUpdated, this, &Keybind_TableModel::updateKeybindMapFromDB);
    connect(_keybindDB, &Keybind_DB::keyInfoUpdated, this, &Keybind_TableModel::updateKeyAppellationHashFromDB);
    connect(_keybindDB, &Keybind_DB::functionInfoUpdated, this, &Keybind_TableModel::updateFunctionNameHashFromDB);

    connect(_keybindDB, &Keybind_DB::keyBindUpdated, this, &Keybind_TableModel::updateModelData);
    connect(_keybindDB, &Keybind_DB::keyInfoUpdated, this, &Keybind_TableModel::updateModelData);
    connect(_keybindDB, &Keybind_DB::functionInfoUpdated, this, &Keybind_TableModel::updateModelData);
}



// [从数据库更新]

void Keybind_TableModel::updateKeyAppellationHashFromDB()
{
    _keyAppellationHash.clear();
    _keyAppellationHash = _keybindDB->getKeyAppellation();
    dataChanged(index(0, 0), index(rowCount() - 1, 0));
}

void Keybind_TableModel::updateFunctionNameHashFromDB()
{
    _functionNameHash.clear();
    _functionNameHash = _keybindDB->getFunctionName();
    dataChanged(index(0, 1), index(rowCount() - 1, 1));
}

void Keybind_TableModel::updateModelData()
{
    _modelData.clear();
    _modelData = _keybindDB->getKeyBindModelData();
    setModelData(_modelData);
}

// [Mouse Event]

void Keybind_TableModel::setSelectedIndex(const QModelIndex& index) {
    _selectedIndex = index;
}

void Keybind_TableModel::setHoveredIndex(const QModelIndex& index) {
    _hoveredIndex = index;
}

QModelIndex Keybind_TableModel::getSelectedIndex() const {
    return _selectedIndex;
}

QModelIndex Keybind_TableModel::getHoveredIndex() const {
    return _hoveredIndex;
}

QModelIndex Keybind_TableModel::getShowIndex() const
{
    if (_hoveredIndex.isValid()) {
        return _hoveredIndex;
    }
    if (_selectedIndex.isValid()) {
        return _selectedIndex;
    }
    return QModelIndex();
}

bool Keybind_TableModel::replaceKeybind(const QModelIndex& keyIndex, const QString& functionID)
{
    if (!keyIndex.isValid() || keyIndex.row() >= rowCount() || keyIndex.column() >= columnCount()) {
        return false;
    }

    TableStructs::KeybindItem item = _modelData.at(keyIndex.row());
    if (item.FunctionID == functionID) {
        return false;
    }

    _keybindUndoStack.push(item);
    item.FunctionID = functionID;
    _keybindHistoryQueue.enqueue(item);

    setRowData(keyIndex.row(), item);
    emit selectedIndexChanged(keyIndex);

    return true;
}

bool Keybind_TableModel::undoReplaceKeybind()
{
    if (_keybindUndoStack.empty()) {
        return false;
    }

    TableStructs::KeybindItem item = _keybindUndoStack.pop();
    _keybindHistoryQueue.enqueue(item);

    QModelIndex index = getIndexByKeyID(item.KeyID);
    setRowData(index.row(), item);
    emit selectedIndexChanged(index);

    return true;
}

bool Keybind_TableModel::appllyReplaceKeybindToDB()
{
    // 预处理_keybindHistoryQueue，以避免重复替换
    QMap<QString, TableStructs::KeybindItem> lastUpdates;

    while (!_keybindHistoryQueue.empty()) {
        TableStructs::KeybindItem item = _keybindHistoryQueue.dequeue();
        lastUpdates[item.KeyID] = item; // 覆盖同一 key_id 的先前条目
    }

    // 遍历 lastUpdates，将替换写入数据库
    for (const TableStructs::KeybindItem& item : lastUpdates) {
        if (!_keybindDB->replaceKeybind(item.KeyID, item.FunctionID)) {
            _keybindHistoryQueue.clear();
            updateModelData();
            qWarning() << "[Keybind_TableModel::appllyReplaceKeybindToDB] replaceKeybind failed! " << item.KeyID <<  ", " << item.FunctionID;
            qWarning() << "[Keybind_TableModel::appllyReplaceKeybindToDB] start to refresh model data!!!";
            return false;
        }
    }

    return true;
}

bool Keybind_TableModel::hasUnsavedReplaceKeybind() const
{
    return !_keybindHistoryQueue.isEmpty();
}

