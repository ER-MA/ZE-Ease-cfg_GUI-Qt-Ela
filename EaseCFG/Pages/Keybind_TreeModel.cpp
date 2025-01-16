#include "Keybind_TreeModel.h"
#include "Proc_TreeData.h"

Keybind_TreeModel::Keybind_TreeModel(Keybind_DB* keybindDB, QObject* parent)
    : QAbstractItemModel(parent), _keybindDB(keybindDB)
{
    // 初始化根节点
    QVariantList rootData;
    rootData << "FunctionName" << "FunctionID" << "ParentID"; // 根节点，同时用于存储列名
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
    // 获取数据并构建树形结构
    QList<TableStructs::FunctionModelItem> dataList = _keybindDB->getFunctionInfoModelData();

    Proc_TreeData* treeData = new Proc_TreeData();
    for (const auto& item : dataList) {
        treeData->addNode(item.Name, item.FunctionID, item.ParentID);
    }

    QList<TreeNode*> rootNodes = treeData->buildTree();
    //for (const auto& rootNode : rootNodes)
    //    printTree(rootNode); // 打印树形结构
    
    // 从根节点开始插入
    for (const auto& rootNode : rootNodes) {
        insertNode(_rootItem.get(), rootNode);
    }

    // 清理和释放内存
    delete treeData;
}

// 辅助函数，用于递归打印树节点
void Keybind_TreeModel::printTree(const TreeNode* node, int level) {
    QString indent;
    for (int i = 0; i < level; ++i) {
        indent += "  "; // 添加缩进以表示层级
    }
    qDebug() << indent << "Node:" << node->Name << "FunctionID:" << node->FunctionID << "ParentID:" << node->ParentID;
    for (const auto& child : node->children) {
        printTree(child, level + 1); // 递归打印子节点
    }
}

// 辅助函数，用于递归插入树节点
void Keybind_TreeModel::insertNode(Univ_TreeItem* parentItem, const TreeNode* treeNode) {
    // 插入新节点到父节点
    int position = parentItem->childCount();
    if (!parentItem->insertChildren(position, 1, parentItem->columnCount())) {
        // 处理插入失败的情况
        qDebug() << "[Keybind_TreeModel::insertNode] Insert child failed:" << parentItem->data(0) << "->" << treeNode->Name;
        return;
    }

    // 设置新节点的数据
    Univ_TreeItem* newItem = parentItem->child(position);
    newItem->setData(0, treeNode->Name);
    newItem->setData(1, treeNode->FunctionID);
    newItem->setData(2, treeNode->ParentID);

    // 递归插入子节点
    for (const auto& childNode : treeNode->children) {
        insertNode(newItem, childNode);
    }
}

QString Keybind_TreeModel::getFunctionId(const QModelIndex& index) const {
    Univ_TreeItem* item = getItem(index);
    if (item && item != _rootItem.get()) {
        return item->data(1).toString(); // function_id存储在第二列
    }
    return QString();
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
    //if (parent.isValid())
    //    return getItem(parent)->columnCount();
    //return _rootItem->columnCount();

    // 修改以使得TreeView仅显示第一列
    Q_UNUSED(parent);
    return 1;
}

QVariant Keybind_TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Univ_TreeItem* item = getItem(index);

    //if (role == Qt::DisplayRole || role == Qt::EditRole)
    //    return item->data(index.column());

    // 修改以使得TreeView仅显示第一列
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0) {
            return item->data(0);
        }
    }

    return QVariant();
}

QVariant Keybind_TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    //    return _rootItem->data(section);

    // 修改以使得TreeView仅显示第一列
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return _rootItem->data(0);
        }
    }

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
