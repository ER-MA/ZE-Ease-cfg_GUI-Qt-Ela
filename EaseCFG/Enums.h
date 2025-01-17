#ifndef ENUMS_H
#define ENUMS_H

#include <QMetaEnum>

enum class MouseState : int {
    SelectRole = Qt::UserRole + 1,
    HoverRole = Qt::UserRole + 2,
};

#endif // ENUMS_H

