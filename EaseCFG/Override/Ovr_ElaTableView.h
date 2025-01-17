#ifndef OVR_ELATABLEVIEW_H
#define OVR_ELATABLEVIEW_H

#include "ElaTableView.h"
#include <QMouseEvent>
#include <QModelIndex>

class Ovr_ElaTableView : public ElaTableView {
    Q_OBJECT

public:
    explicit Ovr_ElaTableView(QWidget* parent = nullptr);

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

#endif // OVR_ELATABLEVIEW_H
