#include "myanimationbutton.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
myAnimationButton::myAnimationButton(QWidget *parent) : QWidget(parent)

{
    imageWidth = 0;
    imageHeight = 0;
    originalWidth = 0;
    originalHeight = 0;
    newWidth = 0;
    newHeight = 0;
    imagePath = "";


    enterAnimation = new QPropertyAnimation(this, "");
    enterAnimation->setStartValue(0);
    enterAnimation->setEndValue(25);
    enterAnimation->setDuration(200);
    connect(enterAnimation,
            &QPropertyAnimation::valueChanged,
            this,
            &myAnimationButton::enterImageChanged);

    leaveAnimation = new QPropertyAnimation(this, "");
    leaveAnimation->setStartValue(0);
    leaveAnimation->setEndValue(25);
    leaveAnimation->setDuration(200);
    connect(leaveAnimation,
            &QPropertyAnimation::valueChanged,
            this,
            &myAnimationButton::leaveImageChanged);

    //    dialog = new QRcodeDialog(this);
}

myAnimationButton::~myAnimationButton()
{
    delete enterAnimation;
    delete leaveAnimation;
}

void myAnimationButton::enterImageChanged(QVariant value)
{
    newWidth = imageWidth + value.toInt();
    newHeight = imageHeight + value.toInt();
    update();
}

void myAnimationButton::leaveImageChanged(QVariant value)
{
    newWidth = imageWidth - value.toInt();
    newHeight = imageHeight - value.toInt();
    update();
}

void myAnimationButton::setImagePath(QString path)
{
    imagePath = path;
    QPixmap img(path);
    imageWidth = img.width();
    imageHeight = img.height();
    originalWidth = imageWidth;
    originalHeight = imageHeight;
    newWidth = imageWidth - 25;
    newHeight = imageHeight - 25;
    update();
}

void myAnimationButton::enterEvent(QEvent *event)
{
    imageWidth = imageWidth - 25;
    imageHeight = imageHeight - 25;
    enterAnimation->start();
}

void myAnimationButton::leaveEvent(QEvent *event)
{
    imageWidth = originalWidth;
    imageHeight = originalHeight;
    leaveAnimation->start();
}

void myAnimationButton::paintEvent(QPaintEvent *event)
{
    if (imagePath.isEmpty())
        return;

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);

    QPixmap img(imagePath);
    img = img.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int pixX = rect().center().x() - newWidth / 2;
    int pixY = rect().center().y() - newHeight / 2 - 10;
    QPoint point(pixX, pixY);
    paint.drawPixmap(point, img);
    paint.drawText(QRectF(0, height() - 20, width(), 20), Qt::AlignCenter, text);
    QRect r = rect();
    r.adjust(0, 0, -1, -1);
    paint.drawRect(r);
}

void myAnimationButton::mousePressEvent(QMouseEvent *event)
{
    if(imagePath.isEmpty())
        return;

    QPixmap image(imagePath);
    if(image.rect().contains(event->pos()))
    {
        qDebug()<<"press";
//        dialog->show();
    }

}





