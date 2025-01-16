#ifndef UNIV_TREEITEM_H
#define UNIV_TREEITEM_H

#include <QTreeWidgetItem>
#include <QVariantList>
#include <vector>
#include <memory>

class Univ_TreeItem
{
public:
    explicit Univ_TreeItem(QVariantList data, Univ_TreeItem* parent = nullptr);
    ~Univ_TreeItem();

    // 返回当前节点的第number个子节点
    Univ_TreeItem* child(int number);
    // 返回当前节点的父节点
    Univ_TreeItem* parent();

    // 返回当前节点的，子节点数量
    int childCount() const;
    // 返回当前节点的，列数
    int columnCount() const;
    // 返回当前节点中，第column列的数据
    QVariant data(int column) const;
    // 设置当前节点中，第column列的数据
    bool setData(int column, const QVariant &value);

    // 在position处，插入count个子节点，每行有columns列数据
    bool insertChildren(int position, int count, int columns);
    // 在position处，插入columns列数据
    bool insertColumns(int position, int columns);
    // 在position处，移除count个子节点
    bool removeChildren(int position, int count);
    // 在position处，移除columns列数据
    bool removeColumns(int position, int columns);

    int row() const;

private:
    std::vector<std::unique_ptr<Univ_TreeItem>> m_childItems;
    QVariantList itemData;
    Univ_TreeItem *m_parentItem;
};

#endif // UNIV_TREEITEM_H
