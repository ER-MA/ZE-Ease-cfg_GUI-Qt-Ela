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
};

#endif // KEYBIND_TREEMODEL_H
