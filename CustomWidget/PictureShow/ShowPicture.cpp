#include "ShowPicture.h"

ShowPicture::ShowPicture(QWidget *parent) : QQuickWidget(parent)
{
    QUrl source("qrc:/main.qml");
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setSource(source);
}
