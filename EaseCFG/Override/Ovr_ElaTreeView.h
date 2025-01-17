#ifndef OVR_ELATREEVIEW_H
#define OVR_ELATREEVIEW_H

#include "ElaTreeView.h"

#include <QDebug>
#include <QMouseEvent>
#include <QModelIndex>

class Ovr_ElaTreeView : public ElaTreeView {
    Q_OBJECT

public:
    explicit Ovr_ElaTreeView(QWidget* parent = nullptr);

signals:
    void hoverIndexChang(const QModelIndex& index);
    void selectIndexChang(const QModelIndex& index);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QModelIndex _currentHoverIndex;
    QModelIndex _lastHoverIndex;
};

#endif // OVR_ELATREEVIEW_H
