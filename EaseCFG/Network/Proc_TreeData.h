#ifndef PROC_TREEDATA_H
#define PROC_TREEDATA_H

#include <QObject>
#include <QVariant>

struct TreeNode {
    QString Name;
    QString FunctionID;
    QString ParentID;
    QList<TreeNode*> children;

    TreeNode(const QString& name, const QString& functionID, const QString& parentID)
        : Name(name), FunctionID(functionID), ParentID(parentID) {}

    ~TreeNode() {
        qDeleteAll(children);
    }
};

class Proc_TreeData : public QObject
{
    Q_OBJECT
public:
    explicit Proc_TreeData(QObject *parent = nullptr);
    ~Proc_TreeData();

    void addNode(const QString& name, const QString& functionID, const QString& parentID);
    QList<TreeNode*> buildTree();

private:
    QMap<QString, TreeNode*> nodesByFunctionID;
    QMap<QString, QList<TreeNode*>> parentChildMap;
    QList<TreeNode*> rootNodes;
};

#endif // PROC_TREEDATA_H
