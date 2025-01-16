#ifndef KEYBIND_TREEMODEL_H
#define KEYBIND_TREEMODEL_H

#include <QAbstractItemModel>
#include "Univ_TreeItem.h"
#include "Keybind_DB.h"

class Keybind_TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Keybind_TreeModel(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Keybind_TreeModel();

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool insertRows(int position, int rows, const QModelIndex& parent) override;
    bool removeRows(int position, int rows, const QModelIndex& parent) override;
    bool insertColumns(int position, int columns, const QModelIndex& parent) override;
    bool removeColumns(int position, int columns, const QModelIndex& parent) override;

    void setModelData(Univ_TreeItem* item);

private:
    Univ_TreeItem* getRootItem() const;
    Univ_TreeItem* getItem(const QModelIndex& index) const;

    void updateModelData();

    Univ_TreeItem* m_rootItem;

    Keybind_DB* _keybindDB; // 数据库对象

    // 重写一次声明，以理清头绪
    // 首先是通用的声明，暂不使用Univ_TreeItem*作为参数类型。
    
    // 返回子索引；传入所属父索引，及其所在的行号、列号
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    // 返回父索引；传入子索引
    QModelIndex parent(const QModelIndex& index) const override;
    // 返回行数；传入父索引
    int rowCount(const QModelIndex& parent) const override;
    // 返回列数；传入父索引
    int columnCount(const QModelIndex& parent) const override;
    // 返回数据；传入索引、角色
    QVariant data(const QModelIndex& index, int role) const override;

    // 以上函数仅实现了数据的只读模式，数据编辑需要setData函数，增删数据项还需要其他函数。

    // 从指定索引的row行处起，插入count行数据
    bool insertRows(int row, int count, const QModelIndex& parent) override;
    // 从指定索引的row行处开始，连续删除count行数据
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    // 从指定索引的column列处起，插入count列数据
    bool insertColumns(int column, int count, const QModelIndex& parent) override;
    // 从指定索引的column列处开始，连续删除count列数据
    bool removeColumns(int column, int count, const QModelIndex& parent) override;
};

#endif // KEYBIND_TREEMODEL_H
