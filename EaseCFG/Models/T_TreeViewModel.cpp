#include "T_TreeViewModel.h"

#include <QIcon>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "T_TreeItem.h"


T_TreeViewModel::T_TreeViewModel(QObject* parent)
    : QAbstractItemModel{ parent }
{
    _rootItem = new T_TreeItem("root", "", nullptr); // 修改以接受英文键
}

T_TreeViewModel::~T_TreeViewModel()
{
    delete _rootItem;
}

void T_TreeViewModel::loadJsonData(const QByteArray& jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonObject jsonObj = doc.object();
    QJsonArray items = jsonObj["items"].toArray();

    foreach(const QJsonValue & itemValue, items) {
        processItem(itemValue.toObject(), _rootItem);
    }
}

// 新增一个递归函数来处理每一项及其子项
void T_TreeViewModel::processItem(const QJsonObject& itemObj, T_TreeItem* parentItem)
{
    QString enKey = itemObj["en_key"].toString();
    QString zhText = itemObj["zh_text"].toString();
    T_TreeItem* item = new T_TreeItem(zhText, enKey, parentItem);
    parentItem->appendChildItem(item);
    _itemsMap.insert(enKey, item);  // 使用英文键作为键值

    if (itemObj.contains("children")) {  // 检查是否存在"children"字段
        QJsonArray children = itemObj["children"].toArray();
        foreach(const QJsonValue & childValue, children) {
            processItem(childValue.toObject(), item);  // 递归调用自身处理子项
        }
    }
}

QModelIndex T_TreeViewModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }
    T_TreeItem* childItem = static_cast<T_TreeItem*>(child.internalPointer());
    T_TreeItem* parentItem = childItem->getParentItem();
    if (parentItem == _rootItem)
    {
        return QModelIndex();
    }
    else if (parentItem == nullptr)
    {
        return QModelIndex();
    }
    return createIndex(parentItem->getRow(), 0, parentItem);
}

QModelIndex T_TreeViewModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }
    T_TreeItem* parentItem;
    if (!parent.isValid())
    {
        parentItem = _rootItem;
    }
    else
    {
        parentItem = static_cast<T_TreeItem*>(parent.internalPointer());
    }
    T_TreeItem* childItem = nullptr;
    if (parentItem->getChildrenItems().count() > row)
    {
        childItem = parentItem->getChildrenItems().at(row);
    }
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

int T_TreeViewModel::rowCount(const QModelIndex& parent) const
{
    T_TreeItem* parentItem;
    if (parent.column() > 0)
    {
        return 0;
    }
    if (!parent.isValid())
    {
        parentItem = _rootItem;
    }
    else
    {
        parentItem = static_cast<T_TreeItem*>(parent.internalPointer());
    }
    return parentItem->getChildrenItems().count();
}

int T_TreeViewModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant T_TreeViewModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    T_TreeItem* item = static_cast<T_TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->getItemTitle();
    }
    else if (role == Qt::UserRole)
    {
        return item->getEnKey();  // 返回英文键
    }
    else if (role == Qt::DecorationRole)
    {
        return QIcon(":/Resource/Image/Cirno.jpg");
    }
    else if (role == Qt::CheckStateRole)
    {
        if (item->getIsHasChild())
        {
            return item->getChildCheckState();
        }
        else
        {
            return item->getIsChecked() ? Qt::Checked : Qt::Unchecked;
        }
        return Qt::Unchecked;
    }
    return QVariant();
}

bool T_TreeViewModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        T_TreeItem* item = static_cast<T_TreeItem*>(index.internalPointer());
        item->setIsChecked(!item->getIsChecked());
        item->setChildChecked(item->getIsChecked());
        Q_EMIT dataChanged(QModelIndex(), QModelIndex(), {role});
        return true;
    }
    return QAbstractItemModel::setData(index, value, role);
}

Qt::ItemFlags T_TreeViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsUserCheckable;
    return flags;
}

QVariant T_TreeViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return QString("ElaTreeView-Example-4Level");
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

int T_TreeViewModel::getItemCount() const
{
    return this->_itemsMap.count();
}
