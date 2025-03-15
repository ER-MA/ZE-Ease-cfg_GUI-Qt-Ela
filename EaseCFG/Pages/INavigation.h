// INavigation.h
#pragma once
#include <QString>

class INavigation {
public:
    virtual void navigateTo(const QString& pageKey) = 0;  // 导航函数
    virtual QStringList getAllPageKeys() const = 0;       // 获取所有页面 Key
};
