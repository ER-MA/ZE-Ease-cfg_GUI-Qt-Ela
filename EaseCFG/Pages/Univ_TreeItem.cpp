#include "Univ_TreeItem.h"

Univ_TreeItem::Univ_TreeItem(QVariantList data, Univ_TreeItem* parent)
    : itemData(data),
    m_parentItem(parent)
{

}

Univ_TreeItem::~Univ_TreeItem()
{
    // Unique_ptr will automatically delete child items
}

Univ_TreeItem* Univ_TreeItem::child(int number)
{
    if (number < 0 || number >= m_childItems.size())
        return nullptr;
    return m_childItems.at(number).get();
}

Univ_TreeItem* Univ_TreeItem::parent()
{
    return m_parentItem;
}

int Univ_TreeItem::childCount() const
{
    return m_childItems.size();
}

int Univ_TreeItem::columnCount() const
{
    return itemData.size();
}

QVariant Univ_TreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

bool Univ_TreeItem::setData(int column, const QVariant& value)
{
    if (column < 0 || column >= itemData.size())
        return false;
    itemData[column] = value;
    return true;
}

bool Univ_TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVariantList data(columns);
        m_childItems.insert(m_childItems.begin() + position,
                            std::make_unique<Univ_TreeItem>(data, this));
    }
    return true;
}

bool Univ_TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    for (auto& child : m_childItems)
        child->insertColumns(position, columns);

    return true;
}

bool Univ_TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
        return false;

    m_childItems.erase(m_childItems.begin() + position,
                       m_childItems.begin() + position + count);
    return true;
}

bool Univ_TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    itemData.erase(itemData.begin() + position,
                   itemData.begin() + position + columns);

    for (auto& child : m_childItems)
        child->removeColumns(position, columns);

    return true;
}

bool Univ_TreeItem::appendChild(Univ_TreeItem* childItem)
{
    if (childItem == nullptr)
        return false;
    m_childItems.push_back(std::unique_ptr<Univ_TreeItem>(childItem));
    return true;
}

int Univ_TreeItem::row() const
{
    // 打印指针
    qDebug() << "this: " << this << "parent: " << m_parentItem;
    if (this == nullptr) // 检查 this 是否为 nullptr
        return -1;

    if (m_parentItem)
    {
        for (int i = 0; i < m_parentItem->m_childItems.size(); i++)
        {
            if (m_parentItem->m_childItems.at(i).get() == this)
                return i;
        }
    }
    return -1; // 对于根节点或 this 为 nullptr 的情况，返回 -1
}

