#ifndef ENUMS_H
#define ENUMS_H

#include <QMetaEnum>

enum class MouseState : int {
    SelectRole = Qt::UserRole + 1,
    HoverRole = Qt::UserRole + 2,
};

enum class MessageType : int {
    InformationRole = Qt::UserRole + 3,
    SuccessRole = Qt::UserRole + 4,
    WarningRole = Qt::UserRole + 5,
    ErrorRole = Qt::UserRole + 6,
};

enum class MessageContent : int {
    TopLeftRole = Qt::UserRole + 7,
    TopRightRole = Qt::UserRole + 8,
    BottomLeftRole = Qt::UserRole + 9,
    BottomRightRole = Qt::UserRole + 10,
};

#endif // ENUMS_H

