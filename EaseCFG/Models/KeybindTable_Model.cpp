#include "KeybindTable_Model.h"

KeybindTable_Model::KeybindTable_Model(QObject* parent) : QAbstractTableModel(parent) {
    // 初始化数据
    initModelData();
    initHeaderData();

    //bool ret = setHeaderData(0, Qt::Horizontal, "呀哈哈", Qt::DisplayRole);
    //qDebug() << "setHeaderData ret:" << ret;
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
    _modelData.append(KeybindModelItem{"按键", "等待功能"});
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
