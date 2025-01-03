#include "Ovr_ElaTableView_Hover.h"

Ovr_ElaTableView_Hover::Ovr_ElaTableView_Hover(QWidget* parent)
    : ElaTableView(parent), lastHoverIndex(QModelIndex()) {
    // 鼠标追踪已经在 ElaTableView 中启用，无需再次设置
}

Ovr_ElaTableView_Hover::~Ovr_ElaTableView_Hover() {
    // 析构函数，如果需要清理资源，可以在这里进行
}

void Ovr_ElaTableView_Hover::mouseMoveEvent(QMouseEvent* event) {
    // 首先调用基类的实现以保留原有功能
    ElaTableView::mouseMoveEvent(event);

    // 获取当前鼠标悬停的索引
    QModelIndex currentHoverIndex = indexAt(event->pos());

    // 检查悬停索引是否发生变化
    if (currentHoverIndex != lastHoverIndex) {
        lastHoverIndex = currentHoverIndex;
        // 发射信号通知外界悬停索引已更改
        emit hoveredIndexChanged(currentHoverIndex);
    }
}

void Ovr_ElaTableView_Hover::leaveEvent(QEvent* event) {
    // 首先调用基类的实现以保留原有功能
    ElaTableView::leaveEvent(event);

    // 鼠标离开视图时，悬停索引应设置为无效
    if (lastHoverIndex.isValid()) {
        lastHoverIndex = QModelIndex();
        // 发射信号通知外界悬停索引已更改
        emit hoveredIndexChanged(lastHoverIndex);
    }
}
