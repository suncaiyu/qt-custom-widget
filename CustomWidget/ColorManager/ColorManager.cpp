#include "ColorManager.h"
#include <QDebug>

ColorManager::ColorManager()
{

}

bool ColorManager::IsDarkColor(QColor color)
{
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    qDebug() << r << g << b;
    if (r * 0.299 + g * 0.578 + b * 0.114 >= 192){ //浅色
        return false;
    } else {  //深色
        return true;
    }
}
