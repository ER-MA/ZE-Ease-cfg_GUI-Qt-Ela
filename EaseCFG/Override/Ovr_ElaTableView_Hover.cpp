#include "Ovr_ElaTableView_Hover.h"

Ovr_ElaTableView_Hover::Ovr_ElaTableView_Hover(QWidget* parent)
    : ElaTableView(parent), lastHoverIndex(QModelIndex()) {
    // ���׷���Ѿ��� ElaTableView �����ã������ٴ�����
}

Ovr_ElaTableView_Hover::~Ovr_ElaTableView_Hover() {
    // ���������������Ҫ������Դ���������������
}

void Ovr_ElaTableView_Hover::mouseMoveEvent(QMouseEvent* event) {
    // ���ȵ��û����ʵ���Ա���ԭ�й���
    ElaTableView::mouseMoveEvent(event);

    // ��ȡ��ǰ�����ͣ������
    QModelIndex currentHoverIndex = indexAt(event->pos());

    // �����ͣ�����Ƿ����仯
    if (currentHoverIndex != lastHoverIndex) {
        lastHoverIndex = currentHoverIndex;
        // �����ź�֪ͨ�����ͣ�����Ѹ���
        emit hoveredIndexChanged(currentHoverIndex);
    }
}

void Ovr_ElaTableView_Hover::leaveEvent(QEvent* event) {
    // ���ȵ��û����ʵ���Ա���ԭ�й���
    ElaTableView::leaveEvent(event);

    // ����뿪��ͼʱ����ͣ����Ӧ����Ϊ��Ч
    if (lastHoverIndex.isValid()) {
        lastHoverIndex = QModelIndex();
        // �����ź�֪ͨ�����ͣ�����Ѹ���
        emit hoveredIndexChanged(lastHoverIndex);
    }
}
