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

    Univ_TreeItem *child(int number);
    Univ_TreeItem *parent();

    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);

    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);

    bool appendChild(Univ_TreeItem *childItem);

    int row() const;

private:
    std::vector<std::unique_ptr<Univ_TreeItem>> m_childItems;
    QVariantList itemData;
    Univ_TreeItem *m_parentItem;
};

#endif // UNIV_TREEITEM_H
