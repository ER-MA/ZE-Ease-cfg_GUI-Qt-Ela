#ifndef KEYBIND_TREEMODEL_H
#define KEYBIND_TREEMODEL_H

#include <QAbstractItemModel>
#include "Univ_TreeItem.h"
#include "Keybind_DB.h"

#include "Proc_TreeData.h"

class Keybind_TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Keybind_TreeModel(Keybind_DB* keybindDB, QObject* parent = nullptr);
    ~Keybind_TreeModel();

    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex& parent) override;
    bool removeRows(int position, int rows, const QModelIndex& parent) override;
    bool insertColumns(int position, int columns, const QModelIndex& parent) override;
    bool removeColumns(int position, int columns, const QModelIndex& parent) override;

private:
    Univ_TreeItem* getItem(const QModelIndex& index) const; // 获取TreeItem对象
    std::unique_ptr<Univ_TreeItem> _rootItem; // 根节点

    void setupModelData(); // 设置模型数据
    void printTree(const TreeNode* node, int level = 0); // 辅助函数，用于递归打印树节点
    void insertNode(Univ_TreeItem* parentItem, const TreeNode* treeNode); // 辅助函数，用于插入树节点
    QString getFunctionId(const QModelIndex& index) const;
    Keybind_DB* _keybindDB; // 数据库对象
};

#endif // KEYBIND_TREEMODEL_H
