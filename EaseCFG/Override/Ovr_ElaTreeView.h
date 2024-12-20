#ifndef OVR_ELATREEVIEW_H
#define OVR_ELATREEVIEW_H

#include <QDebug>
#include <QMouseEvent>

#include "ElaTreeView.h"

class Ovr_ElaTreeView : public ElaTreeView {
public:
    explicit Ovr_ElaTreeView(QWidget* parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // OVR_ELATREEVIEW_H
