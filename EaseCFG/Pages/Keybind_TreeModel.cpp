#include "Keybind_TreeModel.h"

Keybind_TreeModel::Keybind_TreeModel(Keybind_DB* keybindDB, QObject* parent)
    : QAbstractItemModel(parent),
      _keybindDB(keybindDB),
      m_rootItem(new Univ_TreeItem(QVariantList() << "functions"))
{
    qDebug() << "Root item1 has " << m_rootItem->columnCount();
    updateModelData();
    qDebug() << "Root item2 has " << m_rootItem->columnCount();
}

Keybind_TreeModel::~Keybind_TreeModel()
{
    delete m_rootItem;
}

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

    Univ_TreeItem* childItem = static_cast<Univ_TreeItem*>(index.internalPointer());
    if (childItem == nullptr) // 检查 childItem 是否为 nullptr
        return QModelIndex();

    Univ_TreeItem* parentItem = childItem->parent();

    if (parentItem == m_rootItem || parentItem == nullptr)
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
    Q_UNUSED(parent);
    return m_rootItem->columnCount();
}

QVariant Keybind_TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    Univ_TreeItem* item = static_cast<Univ_TreeItem*>(index.internalPointer());
    QVariant data = item->data(index.column());
    qDebug() << "Data requested for" << index << "role" << role << "data" << data;
    return item->data(index.column());
}

bool Keybind_TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role != Qt::EditRole || !index.isValid())
        return false;

    Univ_TreeItem* item = static_cast<Univ_TreeItem*>(index.internalPointer());
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, { role });

    return result;
}

Qt::ItemFlags Keybind_TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant Keybind_TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootItem->data(section);

    return QVariant();
}

bool Keybind_TreeModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    Univ_TreeItem* parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, m_rootItem->columnCount());
    endInsertRows();

    return success;
}

bool Keybind_TreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    Univ_TreeItem* parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

bool Keybind_TreeModel::insertColumns(int position, int columns, const QModelIndex& parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = m_rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool Keybind_TreeModel::removeColumns(int position, int columns, const QModelIndex& parent)
{
    bool success = true;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = m_rootItem->removeColumns(position, columns);
    endRemoveColumns();

    return success;
}

void Keybind_TreeModel::setModelData(Univ_TreeItem* newItem)
{
    beginResetModel();
    delete m_rootItem; // 删除原有的根节点
    m_rootItem = newItem; // 设置新的根节点
    endResetModel();
}

Univ_TreeItem* Keybind_TreeModel::getRootItem() const
{
    return m_rootItem;
}

Univ_TreeItem* Keybind_TreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid()) {
        Univ_TreeItem* item = static_cast<Univ_TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return m_rootItem;
}
void Keybind_TreeModel::updateModelData()
{
    QList<QVariantMap> functionList = _keybindDB->getFunctionInfoModelData();
    Univ_TreeItem* newRootItem = new Univ_TreeItem(QVariantList() << "functions"); // 创建新的根节点

    QHash<QString, Univ_TreeItem*> itemMap;

    // 创建所有项，不设置父子关系
    for (const QVariantMap& functionData : functionList) {
        Univ_TreeItem* item = new Univ_TreeItem(QVariantList() << functionData["name_cn"]);
        itemMap[functionData["function_id"].toString()] = item;
    }

    // 设置父子关系
    for (const QVariantMap& functionData : functionList) {
        Univ_TreeItem* item = itemMap[functionData["function_id"].toString()];
        QString parentId = functionData["parent_id"].toString();
        if (parentId.isEmpty() || !itemMap.contains(parentId)) {
            newRootItem->appendChild(item);
        }
        else {
            itemMap[parentId]->appendChild(item);
        }
    }
    setModelData(newRootItem); // 使用新的根节点更新模型数据
}
