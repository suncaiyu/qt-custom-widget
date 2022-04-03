#ifndef COLORMANAGER_H
#define COLORMANAGER_H
#include <QColor>

class ColorManager
{
public:
    ColorManager();
    static bool IsDarkColor(QColor color);
};

#endif // COLORMANAGER_H
