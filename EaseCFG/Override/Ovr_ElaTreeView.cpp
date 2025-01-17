#include "Ovr_ElaTreeView.h"

Ovr_ElaTreeView::Ovr_ElaTreeView(QWidget* parent)
    : ElaTreeView(parent),
    _currentHoverIndex(QModelIndex()),
    _lastHoverIndex(QModelIndex())
{
    
}

void Ovr_ElaTreeView::mouseMoveEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    if (index != _currentHoverIndex && index.isValid()) {
        _currentHoverIndex = index;
        _lastHoverIndex = index;
        emit hoverIndexChang(_currentHoverIndex);
    }

    ElaTreeView::mouseMoveEvent(event);
}

void Ovr_ElaTreeView::leaveEvent(QEvent* event)
{
    _currentHoverIndex = QModelIndex();
    emit hoverIndexChang(_currentHoverIndex);

    ElaTreeView::leaveEvent(event);
}

void Ovr_ElaTreeView::mouseReleaseEvent(QMouseEvent* event)
{
    emit selectIndexChang(_lastHoverIndex);
    ElaTreeView::mouseReleaseEvent(event);
}
