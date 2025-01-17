#include "Ovr_ElaTableView_Hover.h"

Ovr_ElaTableView_Hover::Ovr_ElaTableView_Hover(QWidget* parent)
    : ElaTableView(parent),
    _currentHoverIndex(QModelIndex())
{
    // 鼠标追踪已经在 ElaTableView 中启用，无需再次设置
}

Ovr_ElaTableView_Hover::~Ovr_ElaTableView_Hover()
{

}

void Ovr_ElaTableView_Hover::mouseMoveEvent(QMouseEvent* event)
{
    QModelIndex index = indexAt(event->pos());

    if (index != _currentHoverIndex && index.isValid()) {
        _currentHoverIndex = index;
        _lastHoverIndex = index;
        emit hoverIndexChang(_currentHoverIndex);
    }

    ElaTableView::mouseMoveEvent(event);
}

void Ovr_ElaTableView_Hover::leaveEvent(QEvent* event)
{
    _currentHoverIndex = QModelIndex();
    emit hoverIndexChang(_currentHoverIndex);

    ElaTableView::leaveEvent(event);
}

void Ovr_ElaTableView_Hover::mouseReleaseEvent(QMouseEvent* event)
{
    emit selectIndexChang(_lastHoverIndex);
    ElaTableView::mouseReleaseEvent(event);
}
