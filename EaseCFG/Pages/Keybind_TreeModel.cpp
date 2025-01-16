#include "Keybind_TreeModel.h"

Keybind_TreeModel::Keybind_TreeModel(Keybind_DB* keybindDB, QObject* parent)
    : QAbstractItemModel(parent), _keybindDB(keybindDB)
{
    // 初始化根节点
    QVariantList rootData;
    rootData << "FunctionName" << "FunctionID"; // 根节点，同时用于存储列名
    _rootItem = std::make_unique<Univ_TreeItem>(rootData);
    setupModelData(); // 设置模型数据，具体实现暂时忽略
}

Keybind_TreeModel::~Keybind_TreeModel()
{
    // 根节点会自动删除其子节点
}

// custom functions

void Keybind_TreeModel::setupModelData()
{

}

// override

QModelIndex Keybind_TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Univ_TreeItem* parentItem = getItem(parent);
    Univ_TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex Keybind_TreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    Univ_TreeItem* childItem = getItem(index);
    Univ_TreeItem* parentItem = childItem->parent();

    if (parentItem == _rootItem.get())
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int Keybind_TreeModel::rowCount(const QModelIndex& parent) const
{
    if (parent.column() > 0)
        return 0;

    Univ_TreeItem* parentItem = getItem(parent);
    return parentItem->childCount();
}

int Keybind_TreeModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return getItem(parent)->columnCount();
    return _rootItem->columnCount();
}

QVariant Keybind_TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Univ_TreeItem* item = getItem(index);

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return item->data(index.column());

    return QVariant();
}

QVariant Keybind_TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

Qt::ItemFlags Keybind_TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool Keybind_TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    Univ_TreeItem* item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, { role });

    return result;
}

bool Keybind_TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = _rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

bool Keybind_TreeModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    Univ_TreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    bool success = parentItem->insertChildren(position, rows, _rootItem->columnCount());
    endInsertRows();

    return success;
}

bool Keybind_TreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    Univ_TreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

bool Keybind_TreeModel::insertColumns(int position, int columns, const QModelIndex& parent)
{
    if (position < 0 || position > _rootItem->columnCount())
        return false;

    beginInsertColumns(parent, position, position + columns - 1);
    bool success = _rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool Keybind_TreeModel::removeColumns(int position, int columns, const QModelIndex& parent)
{
    if (position < 0 || position + columns > _rootItem->columnCount())
        return false;

    beginRemoveColumns(parent, position, position + columns - 1);
    bool success = _rootItem->removeColumns(position, columns);
    endRemoveColumns();

    return success;
}

Univ_TreeItem* Keybind_TreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid()) {
        Univ_TreeItem* item = static_cast<Univ_TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem.get();
}
