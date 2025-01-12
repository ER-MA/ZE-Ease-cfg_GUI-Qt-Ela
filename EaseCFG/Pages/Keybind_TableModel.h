#ifndef KEYBIND_TABLE_MODEL_H
#define KEYBIND_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QString>

#include "Keybind_DB.h"
#include "Structs.h"


class Keybind_TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit Keybind_TableModel(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Keybind_TableModel() override;

    void setModelData(const QList<TableStructs::KeybindModelItem>& datas); // 设置数据
    QList<TableStructs::KeybindModelItem> getModelData() const; // 获取数据

    bool updateRowData(int row, const TableStructs::KeybindModelItem& newData); // 更新行数据

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override; // 设置单元格数据
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; //返回单元格数据
    QVariant getKeyID(const QModelIndex& index) const; // 返回单元格KeyID数据
    QVariant getFunctionID(const QModelIndex& index) const; // 返回单元格FunctionID数据

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override; // 设置表头数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // 返回表头数据

    int rowCount(const QModelIndex& parent = QModelIndex()) const override; // 返回行数
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; // 返回列数

    void setSelectedIndex(const QModelIndex& index); // 设置选中单元格索引
    void setHoveredIndex(const QModelIndex& index); // 设置鼠标悬停单元格索引
    QModelIndex getSelectedIndex() const; // 获取选中单元格索引
    QModelIndex getHoveredIndex() const; // 获取鼠标悬停单元格索引
    QModelIndex getShowIndex() const; // 获取显示单元格索引

public slots:

private:
    void initModelData(); // 初始化数据存储
    void initHeaderData(); // 初始化表头数据
    void initConnection(); // 初始化信号连接

    void updateKeybindMapFromDB(); // 更新键位映射表
    void updateKeyAppellationHashFromDB(); // 更新键位释义映射表
    void updateFunctionNameHashFromDB(); // 更新功能名称映射表
    // 上述三个函数暂时用不上，使用下方函数在数据库中使用sql语句直接拼接。
    void updateModelData(); // 更新数据存储

    QMap<QString, QString> _keybindMap; // 键位映射表
    QHash<QString, QString> _keyAppellationHash; // 键位释义映射表
    QHash<QString, QString> _functionNameHash; // 功能名称映射表

    QList<TableStructs::KeybindModelItem> _modelData; // 数据存储
    QList<QString> _horHeaderData; // 水平表头数据
    QList<QString> _verHeaderData; // 垂直表头数据

    Keybind_DB* _keybindDB; // 数据库对象

    QModelIndex _selectedIndex; // 选中单元格索引
    QModelIndex _hoveredIndex; // 鼠标悬停单元格索引
};


#endif // KEYBIND_TABLE_MODEL_H
