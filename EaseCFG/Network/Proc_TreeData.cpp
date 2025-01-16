#include "Proc_TreeData.h"

Proc_TreeData::Proc_TreeData(QObject *parent) : QObject(parent)
{

}

Proc_TreeData::~Proc_TreeData()
{
    qDeleteAll(rootNodes);
    rootNodes.clear();
    nodesByFunctionID.clear();
    parentChildMap.clear();
}

void Proc_TreeData::addNode(const QString& name, const QString& functionID, const QString& parentID) {
    if (nodesByFunctionID.contains(functionID)) {
        // 覆盖已存在的functionID，以避免内存泄漏
        delete nodesByFunctionID[functionID];
    }

    TreeNode* node = new TreeNode(name, functionID, parentID);
    nodesByFunctionID[functionID] = node;

    if (parentID.isEmpty()) {
        rootNodes.append(node);
    }
    else {
        parentChildMap[parentID].append(node);
    }
}

QList<TreeNode*> Proc_TreeData::buildTree() {
    for (auto it = parentChildMap.constBegin(); it != parentChildMap.constEnd(); ++it) {
        QString parentID = it.key();
        if (nodesByFunctionID.contains(parentID)) {
            TreeNode* parentNode = nodesByFunctionID[parentID];
            parentNode->children.append(it.value());
        } else {
            qDebug() << "[Proc_TreeData::buildTree] Parent node not found: " << parentID;
        }
    }
    return rootNodes;
}
