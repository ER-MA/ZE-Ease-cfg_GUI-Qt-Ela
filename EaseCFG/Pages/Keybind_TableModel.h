#ifndef KEYBIND_TABLE_MODEL_H
#define KEYBIND_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QHash>
#include <QStack>
#include <QQueue>

#include "Keybind_DB.h"
#include "Structs.h"
#include "Enums.h"


class Keybind_TableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit Keybind_TableModel(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Keybind_TableModel() override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override; // 设置单元格数据
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override; // 返回单元格数据
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override; // 设置表头数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // 返回表头数据
    int rowCount(const QModelIndex& parent = QModelIndex()) const override; // 返回行数
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; // 返回列数

    // [Custom Function]

    void setModelData(const QList<TableStructs::KeybindItem>& datas); // 设置数据
    QList<TableStructs::KeybindItem> getModelData() const; // 获取数据

    bool setRowData(int row, const TableStructs::KeybindItem& newData); // 设置行数据
    TableStructs::KeybindItem getRowData(int row) const; // 获取行数据

    QVariant getKeyID(const QModelIndex& index);
    QVariant getFunctionID(const QModelIndex& index);

    QModelIndex getIndexByKeyID(const QString& keyID) const; // 返回KeyID对应的索引
    QList<QModelIndex> getIndexByFunctionID(const QString& functionID) const; // 返回FunctionID对应的索引

    // [Mouse Event]

    void setSelectedIndex(const QModelIndex& index); // 设置选中单元格索引
    void setHoveredIndex(const QModelIndex& index); // 设置鼠标悬停单元格索引
    QModelIndex getSelectedIndex() const; // 获取选中单元格索引
    QModelIndex getHoveredIndex() const; // 获取鼠标悬停单元格索引
    QModelIndex getShowIndex() const; // 获取显示单元格索引

    // [Replace Keybind]

    bool replaceKeybind(const QModelIndex& keyIndex, const QString& functionID); // 替换键位
    bool undoReplaceKeybind(); // 撤销替换键位

    // TODO: 缺失错误处理！！！
    bool appllyReplaceKeybindToDB(); // 应用替换键位到数据库

signals:
    void selectedIndexChanged(const QModelIndex& index); // 选中单元格索引改变
    void displayMessaggeBar(const MessageType typeRole, const MessageContent contentRole, const QString& title, const QString& message, const int timeout = 3000);

public slots:

private:
    void initModelData(); // 初始化数据存储
    void initHeaderData(); // 初始化表头数据
    void initConnection(); // 初始化信号连接

    //void updateKeybindMapFromDB(); // 更新键位映射表（弃置）
    void updateKeyAppellationHashFromDB(); // 更新键位释义映射表
    void updateFunctionNameHashFromDB(); // 更新功能名称映射表

    void updateModelData(); // 更新数据存储

    //QMap<QString, QString> _keybindMap; // 键位映射表
    QHash<QString, QString> _keyAppellationHash; // 键位释义映射表
    QHash<QString, QString> _functionNameHash; // 功能名称映射表

    QList<TableStructs::KeybindItem> _modelData; // 数据存储
    QList<QString> _horHeaderData; // 水平表头数据
    QList<QString> _verHeaderData; // 垂直表头数据

    Keybind_DB* _keybindDB; // 数据库对象

    QModelIndex _selectedIndex; // 选中单元格索引
    QModelIndex _hoveredIndex; // 鼠标悬停单元格索引

    
    QStack<TableStructs::KeybindItem> _keybindUndoStack; // 替换键位撤销栈
    QQueue<TableStructs::KeybindItem> _keybindHistoryQueue; // 历史操作队列
};


#endif // KEYBIND_TABLE_MODEL_H
