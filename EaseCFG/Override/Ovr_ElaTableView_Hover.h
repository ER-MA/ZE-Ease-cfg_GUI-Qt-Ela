#ifndef OVR_ELATABLEVIEW_HOVER_H
#define OVR_ELATABLEVIEW_HOVER_H

#include "ElaTableView.h"
#include <QMouseEvent>
#include <QModelIndex>

class Ovr_ElaTableView_Hover : public ElaTableView {
    Q_OBJECT

public:
    explicit Ovr_ElaTableView_Hover(QWidget* parent = nullptr);
    ~Ovr_ElaTableView_Hover();

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

#endif // OVR_ELATABLEVIEW_HOVER_H
