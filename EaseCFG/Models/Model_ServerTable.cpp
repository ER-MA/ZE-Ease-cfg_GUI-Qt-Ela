#include "Model_ServerTable.h"

Model_ServerTable::Model_ServerTable(QObject *parent) :
    QAbstractTableModel(parent) {
    // 初始化数据
    //m_data.append({"ZE #3", "ze_atix_apocalypse_p", "牢大逃亡:归来", "52/64\t(12)"});
    m_data.append({ "Srv #?", "mode_mapname_version", "等待数据", "?/64\t(?)" });
    m_data.append({ "Srv #?", "", "正在尝试获取社区数据", "?/64\t(?)" });
    m_data.append({ "Srv #?", "", "网络连接中", "?/64\t(?)" });
    m_data.append({ "Srv #?", "", "......", "?/64\t(?)" });
    
}

// 返回行数
int Model_ServerTable::rowCount(const QModelIndex &parent) const {
    return m_data.count();
}

// 返回列数
int Model_ServerTable::columnCount(const QModelIndex &parent) const {
    return m_data.isEmpty() ? 0 : m_data.first().count();
}

// 返回单元格数据
QVariant Model_ServerTable::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).at(index.column());
    }
    return QVariant();
}

// 返回表头数据
QVariant Model_ServerTable::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            // 定义表头内容
            switch (section) {
                case 0: return "服务器";
                case 1: return "地图";
                case 2: return "别名";
                case 3: return "人数(余)";
                default: return QVariant();
            }
        }
    }
    return QVariant();
}

void Model_ServerTable::fetchData(const QJsonDocument &serverListJson) {
    // 解析 JSON 数据
    QJsonArray jsonArray = serverListJson.array();

    // 重置数据
    beginResetModel();
    m_data.clear();

    // 填充数据
    for (const QJsonValue& value : jsonArray) {
        QJsonObject serverObject = value.toObject();

        QString displayName = serverObject["DisplayName"].toString();
        QString mapName = serverObject["MapName"].toString();
        QString mapDisplayName = serverObject["MapDisplayName"].toString();
        QString playerCount = serverObject["PlayerCount"].toString();

        m_data.append({ displayName, mapName, mapDisplayName, playerCount });
    }
    qDebug() << "[Model_ServerTable] ...解析完成，数据已填充...";

    endResetModel();
}
