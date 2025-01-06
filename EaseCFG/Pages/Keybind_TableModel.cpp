#include "Keybind_TableModel.h"



Keybind_TableModel::Keybind_TableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // 初始化数据
    initModelData();
    initHeaderData();

    // 可使用 setHeaderData 重新函数设置表头数据
    // bool ret = setHeaderData(0, Qt::Horizontal, "呀哈哈", Qt::DisplayRole);
    // qDebug() << "setHeaderData ret:" << ret;
}

Keybind_TableModel::~Keybind_TableModel()
{
    _modelData.clear();
}

// [ModelData]

void Keybind_TableModel::setModelData(const QList<TableStructs::KeybindModelItem>& datas)
{
    beginResetModel(); // 触发 modelAboutToBeReset 信号

    _modelData = datas;

    endResetModel(); // 触发 modelReset 信号
    //注意：reset model后，选中的item会失效，我们可以自己写保存和恢复选中项的逻辑
    //如果表的行列数是固定的，只是数据变更了，我们可以用 dataChanged 信号来请求刷新。
    //emit dataChanged(index(0,0),index(RowMax-1,ColMax-1),QVector<int>());
}

QList<TableStructs::KeybindModelItem> Keybind_TableModel::getModelData() const
{
    return _modelData;
}

// [RowData]

bool Keybind_TableModel::updateRowData(int row, const TableStructs::KeybindModelItem& newData)
{
    // 修改行数据
    if (row >= 0 && row < _modelData.count()) {
        _modelData[row] = newData;
        emit dataChanged(index(row, 0), index(row, 3), QVector<int>()); // 列数实际为 4，后两个列为前两列的对应ID。
        return true;
    }
    return false;
}

// [ItemData]

bool Keybind_TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    // 设置单元格数据（保存 TableView 中修改的数据）
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        switch (index.column()) {
        case 0: _modelData[row].Key = value.toString(); break;
        case 1: _modelData[row].Function = value.toString(); break;
        }
        emit dataChanged(index, index, QVector<int>());
        return true;
    }
    return false;
}

QVariant Keybind_TableModel::getKeyID(const QModelIndex& index) const
{
    // 返回按键ID ※
    if (!index.isValid()) {
        return QVariant();
    }
    const int row = index.row();
    return _modelData.at(row).KeyID;
}

QVariant Keybind_TableModel::getFunctionID(const QModelIndex& index) const
{
    // 返回功能ID ※
    if (!index.isValid()) {
        return QVariant();
    }
    const int row = index.row();
    return _modelData.at(row).FunctionID;
}

// [HeaderData]

bool Keybind_TableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) {
    // 设置表头数据
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
    // 返回表头数据
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
    // 返回行数
    if (parent.isValid()) {
        return 0;
    }
    return _modelData.count();
}

int Keybind_TableModel::columnCount(const QModelIndex& parent) const {
    // 返回列数
    if (parent.isValid()) {
        return 0;
    }
    return 2;
}

QVariant Keybind_TableModel::data(const QModelIndex& index, int role) const {
    // 返回单元格数据
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        // 显示和编辑做同样处理
        const int row = index.row();
        switch (index.column()) {
        case 0: return _modelData.at(row).Key;
        case 1: return _modelData.at(row).Function;
        }
    }
    return QVariant();
}

// [init]

void Keybind_TableModel::initModelData() {
    // 初始化数据
    _modelData.clear();
    // _modelData.append(KeybindModelItem{"按键", "功能", "按键唯一标识符", "功能唯一标识符"});
    _modelData.append(TableStructs::KeybindModelItem{"Y", "死亡重置", "y", "reset_effect_affected_death"});
    _modelData.append(TableStructs::KeybindModelItem{"NumLock", "一键划刀(轻击)", "numlock", "keep_attack"});
    _modelData.append(TableStructs::KeybindModelItem{"PgDn", "无功能(\"null\")", "pgdn", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"End", "无功能(\"null\")", "end", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"Q", "无功能(\"null\")", "q", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"W", "无功能(\"null\")", "w", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"E", "无功能(\"null\")", "e", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Null", "无功能(\"null\")", "null", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Null", "空功能(\" \")", "null", ""});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Null", "未知功能(\"\?\")", "null", "unknow"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Empty", "无功能(\"null\")", "", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Empty", "空功能(\" \")", "", ""});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Empty", "未知功能(\"\?\")", "", "unknow"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Unknow", "无功能(\"null\")", "unknow", "null"});
    _modelData.append(TableStructs::KeybindModelItem{"[!] Unknow", "空功能(\" \")", "unknow", "" });
    _modelData.append(TableStructs::KeybindModelItem{"[!] Unknow", "未知功能(\"\?\")", "unknow", "unknow"});
}

void Keybind_TableModel::initHeaderData()
{
    // 初始化水平表头数据
    _horHeaderData.clear();
    _horHeaderData.append("按键");
    _horHeaderData.append("功能");

    // 初始化垂直表头数据
    _verHeaderData.clear();
    for (int i = 0; i < _modelData.count(); i++) {
        _verHeaderData.append(QString::number(i + 1));
    }
}

// 在 data() 函数中提取并返回_modelData 对应值
// 在数据发生变化时，使用：
//     beginResetModel(),
//     endResetModel(),
//     beginInsertRows(),
//     endInsertRows(),
//     beginRemoveRows(),
//     endRemoveRows(),
//     dataChanged()
// 等信号通知视图更新。
