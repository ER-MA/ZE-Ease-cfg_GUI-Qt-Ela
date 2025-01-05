#ifndef KEYBIND_TABLE_MODEL_H
#define KEYBIND_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QString>

#include "Structs.h"

class Keybind_TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit Keybind_TableModel(QObject* parent = nullptr);

    void setModelData(const QList<TableStructs::KeybindModelItem>& datas); // 设置数据
    QList<TableStructs::KeybindModelItem> getModelData() const; // 获取数据

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // 返回表头数据
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override; // 设置表头数据
    int rowCount(const QModelIndex& parent = QModelIndex()) const override; // 返回行数
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; // 返回列数
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; //返回单元格数据
    QVariant dataKeyID(const QModelIndex& index) const; // 返回单元格KeyID数据
    QVariant dataFunctionID(const QModelIndex& index) const; // 返回单元格FunctionID数据
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override; // 设置单元格数据
    bool updateRowData(int row, const TableStructs::KeybindModelItem& newData);



public slots:

private:
    void initModelData(); // 初始化数据存储
    void initHeaderData(); // 初始化表头数据

    QList<TableStructs::KeybindModelItem> _modelData; // 数据存储
    QList<QString> _horHeaderData; // 水平表头数据
    QList<QString> _verHeaderData; // 垂直表头数据
};

#endif // KEYBIND_TABLE_MODEL_H
