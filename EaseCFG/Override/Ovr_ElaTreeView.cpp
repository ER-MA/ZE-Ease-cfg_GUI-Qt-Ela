#include "Ovr_ElaTreeView.h"

Ovr_ElaTreeView::Ovr_ElaTreeView(QWidget* parent) : ElaTreeView(parent) {
    setMouseTracking(true);
}

void Ovr_ElaTreeView::mouseMoveEvent(QMouseEvent* event) {
    // 获取鼠标在QTreeView中的位置
    QPoint globalPos = event->globalPos();
    QPoint viewPos = mapFromGlobal(globalPos);

    // 计算鼠标在QTreeView中的行列位置
    QModelIndex index = indexAt(viewPos);

    // 检查是否为有效的索引
    if (index.isValid()) {
        // 获取节点的中文文本
        QString text = index.data(Qt::DisplayRole).toString();
        qDebug() << "Mouse over node: " << text;
    }
    else {
        qDebug() << "Mouse outside any node";
    }

    // 调用父类的mouseMoveEvent，以保持原有功能
    QTreeView::mouseMoveEvent(event);
}
