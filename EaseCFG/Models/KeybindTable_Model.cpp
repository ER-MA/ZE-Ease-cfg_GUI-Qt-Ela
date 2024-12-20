#include "KeybindTable_Model.h"

KeybindTableModel::KeybindTableModel(QObject* parent) : QAbstractTableModel(parent) {
    // 初始化数据
    m_data.append(QStringList{"按键", "等待功能"});
}

// 返回行数
int KeybindTableModel::rowCount(const QModelIndex& parent) const {
    return m_data.count();
}

// 返回列数
int KeybindTableModel::columnCount(const QModelIndex& parent) const {
    return m_data.isEmpty() ? 0 : m_data.first().count();
}

// 返回单元格数据
QVariant KeybindTableModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).at(index.column());
    }
    return QVariant();
}

// 返回表头数据
QVariant KeybindTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            // 定义表头内容
            switch (section) {
            case 0: return "按键";
            case 1: return "功能";
            default: return QVariant();
            }
        }
    }
    return QVariant();
}

// 设置单元格数据
void KeybindTableModel::fetchData(const QJsonDocument& jsonDoc) {
    // 解析 JSON 数据
    QJsonArray jsonArray = jsonDoc.array();

    // 重置数据
    beginResetModel();
    m_data.clear();

    // 填充数据
    for (int i = 0; i < jsonArray.count(); i++) {
        // 此处填充数据的逻辑需要根据具体的 JSON 结构来实现
    }

    endResetModel();
}
