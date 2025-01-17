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

    QVariant getFunctionID(const QModelIndex& index) const;

    void setSelectedIndex(const QModelIndex& index); // 设置选中单元格索引
    void setHoveredIndex(const QModelIndex& index); // 设置鼠标悬停单元格索引
    QModelIndex getSelectedIndex() const; // 获取选中单元格索引
    QModelIndex getHoveredIndex() const; // 获取鼠标悬停单元格索引
    QModelIndex getShowIndex() const; // 获取显示单元格索引

private:
    Univ_TreeItem* getItem(const QModelIndex& index) const; // 获取TreeItem对象
    std::unique_ptr<Univ_TreeItem> _rootItem; // 根节点

    void initConnections(); // 初始化信号连接
    void setupModelData(); // 设置模型数据
    void printTree(const TreeNode* node, int level = 0); // 辅助函数，用于递归打印树节点
    void insertNode(Univ_TreeItem* parentItem, const TreeNode* treeNode); // 辅助函数，用于插入树节点
    Keybind_DB* _keybindDB; // 数据库对象

    QModelIndex _selectedIndex; // 选中单元格索引
    QModelIndex _hoveredIndex; // 鼠标悬停单元格索引
};

#endif // KEYBIND_TREEMODEL_H
