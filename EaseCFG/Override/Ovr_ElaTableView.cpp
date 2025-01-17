#include "Ovr_ElaTableView.h"

Ovr_ElaTableView::Ovr_ElaTableView(QWidget* parent)
    : ElaTableView(parent),
    _currentHoverIndex(QModelIndex()),
    _lastHoverIndex(QModelIndex())
{
    // 鼠标追踪已经在 ElaTableView 中启用，无需再次设置
}

void Ovr_ElaTableView::mouseMoveEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    if (index != _currentHoverIndex && index.isValid()) {
        _currentHoverIndex = index;
        _lastHoverIndex = index;
        emit hoverIndexChang(_currentHoverIndex);
    }

    ElaTableView::mouseMoveEvent(event);
}

void Ovr_ElaTableView::leaveEvent(QEvent* event)
{
    _currentHoverIndex = QModelIndex();
    emit hoverIndexChang(_currentHoverIndex);

    ElaTableView::leaveEvent(event);
}

void Ovr_ElaTableView::mouseReleaseEvent(QMouseEvent* event)
{
    emit selectIndexChang(_lastHoverIndex);
    ElaTableView::mouseReleaseEvent(event);
}
