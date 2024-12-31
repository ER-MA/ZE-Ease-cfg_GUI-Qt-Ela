#include "KeybindTable_Model.h"

KeybindTable_Model::KeybindTable_Model(QObject* parent) : QAbstractTableModel(parent) {
    // 初始化数据
    initModelData();
    initHeaderData();

    // 可使用 setHeaderData 重新函数设置表头数据
    // bool ret = setHeaderData(0, Qt::Horizontal, "呀哈哈", Qt::DisplayRole);
    // qDebug() << "setHeaderData ret:" << ret;
}



void KeybindTable_Model::setModelData(const QList<KeybindModelItem>& datas)
{
    beginResetModel(); // 触发 modelAboutToBeReset 信号
    _modelData = datas;


    endResetModel(); // 触发 modelReset 信号
    //注意：reset model后，选中的item会失效，我们可以自己写保存和恢复选中项的逻辑
    //如果表的行列数是固定的，只是数据变更了，我们可以用 dataChanged 信号来请求刷新。
    //emit dataChanged(index(0,0),index(RowMax-1,ColMax-1),QVector<int>());
}

QList<KeybindModelItem> KeybindTable_Model::getModelData() const
{
    return _modelData;
}



bool KeybindTable_Model::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role) {
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

QVariant KeybindTable_Model::headerData(int section, Qt::Orientation orientation, int role) const {
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

int KeybindTable_Model::rowCount(const QModelIndex& parent) const {
    // 返回行数
    if (parent.isValid()) {
        return 0;
    }
    return _modelData.count();
}

int KeybindTable_Model::columnCount(const QModelIndex& parent) const {
    // 返回列数
    if (parent.isValid()) {
        return 0;
    }
    return 2;
}

QVariant KeybindTable_Model::data(const QModelIndex& index, int role) const {
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

QVariant KeybindTable_Model::dataKeyID(const QModelIndex& index) const
{
    // 返回按键ID ※
    if (!index.isValid()) {
        return QVariant();
    }
    const int row = index.row();
    return _modelData.at(row).KeyID;
}

QVariant KeybindTable_Model::dataFunctionID(const QModelIndex& index) const
{
    // 返回功能ID ※
    if (!index.isValid()) {
        return QVariant();
    }
    const int row = index.row();
    return _modelData.at(row).FunctionID;
}

bool KeybindTable_Model::setData(const QModelIndex& index, const QVariant& value, int role)
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



void KeybindTable_Model::initModelData() {
    // 初始化数据
    _modelData.clear();
    _modelData.append(KeybindModelItem{"按键", "等待功能", "按键唯一标识符", "功能唯一标识符"});
    _modelData.append(KeybindModelItem{"Y", "死亡重置", "y", "reset_effect_affected_death"});
    _modelData.append(KeybindModelItem{"NumLock", "一键划刀(轻击)", "numlock", "keep_attack"});
    _modelData.append(KeybindModelItem{"PgDn", "空（无功能）", "pgdn", "null"});
    _modelData.append(KeybindModelItem{"End", "?", "end", ""});
    _modelData.append(KeybindModelItem{"Key02", "Function02", "KeyID:02", "FunctionID:02"});
    _modelData.append(KeybindModelItem{"Key03", "Function03", "KeyID:03", "FunctionID:03"});
    _modelData.append(KeybindModelItem{"Key04", "Function04", "KeyID:04", "FunctionID:04"});
    _modelData.append(KeybindModelItem{"Key05", "Function05", "KeyID:05", "FunctionID:05"});
    _modelData.append(KeybindModelItem{"Key06", "Function06", "KeyID:06", "FunctionID:06"});
    _modelData.append(KeybindModelItem{"Key07", "Function07", "KeyID:07", "FunctionID:07"});
    _modelData.append(KeybindModelItem{"Key08", "Function08", "KeyID:08", "FunctionID:08"});
    _modelData.append(KeybindModelItem{"Key09", "Function09", "KeyID:09", "FunctionID:09"});        
    _modelData.append(KeybindModelItem{"Key10", "Function10", "KeyID:10", "FunctionID:10"});
    _modelData.append(KeybindModelItem{"Key11", "Function11", "KeyID:11", "FunctionID:11"});
    _modelData.append(KeybindModelItem{"Key12", "Function12", "KeyID:12", "FunctionID:12"});
    _modelData.append(KeybindModelItem{"Key13", "Function13", "KeyID:13", "FunctionID:13"});
    _modelData.append(KeybindModelItem{"Key14", "Function14", "KeyID:14", "FunctionID:14"});
    _modelData.append(KeybindModelItem{"Key15", "Function15", "KeyID:15", "FunctionID:15"});
    _modelData.append(KeybindModelItem{"Key16", "Function16", "KeyID:16", "FunctionID:16"});
    _modelData.append(KeybindModelItem{"Key17", "Function17", "KeyID:17", "FunctionID:17"});
    _modelData.append(KeybindModelItem{"Key18", "Function18", "KeyID:18", "FunctionID:18"});
    _modelData.append(KeybindModelItem{"Key19", "Function19", "KeyID:19", "FunctionID:19"});
    _modelData.append(KeybindModelItem{"Key20", "Function20", "KeyID:20", "FunctionID:20"});
    _modelData.append(KeybindModelItem{"Key21", "Function21", "KeyID:21", "FunctionID:21"});
    _modelData.append(KeybindModelItem{"...", "...", "...", "..."});
    _modelData.append(KeybindModelItem{"...", "..."});
}

void KeybindTable_Model::initHeaderData()
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
