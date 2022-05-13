#include "RotatingCard.h"
#include <QPainter>
#include <QMouseEvent>

RotatingCard::RotatingCard(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    animationX.setTargetObject(this);
    animationX.setPropertyName("cardAngleX");
    animationY.setTargetObject(this);
    animationY.setPropertyName("cardAngleY");
    animationX.setDuration(200);
    animationY.setDuration(200);
}

RotatingCard::~RotatingCard()
{

}

void RotatingCard::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QTransform transform = p.transform();
    transform.translate(width() / 2, height() / 2);
    transform.rotate(mCard.angleX, Qt::XAxis);
    transform.rotate(mCard.angleY, Qt::YAxis);
    transform.translate(-width() / 2, -height() / 2);
    p.setTransform(transform);
    p.drawPixmap(QRect(mCard.mStartPoint, mCard.mSize), mCard.mPixmap);
}

void RotatingCard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    mCard.mStartPoint = rect().center() - QPoint(mCard.mSize.width() / 2, mCard.mSize.height() / 2);
    setMinimumSize(mCard.mSize);
}

void RotatingCard::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (QRect(mCard.mStartPoint, mCard.mSize).contains(pos)) {
        if (animationX.state() == QPropertyAnimation::Running) {
            animationX.stop();
        }
        if (animationY.state() == QPropertyAnimation::Running) {
            animationY.stop();
        }
        qreal maxDistanceX = mCard.mSize.width() / 2.0;
        qreal maxDistanceY = mCard.mSize.height() / 2.0;
        QPoint center = rect().center();
        QPoint distancePos = pos - center;
        mCard.angleX = -distancePos.y() / maxDistanceY * mCard.maxAngle;
        mCard.angleY = -distancePos.x() / maxDistanceX * mCard.maxAngle;
//        qDebug() << distancePos.x() / maxDistanceX;
    } else {
        if (animationX.state() == QPropertyAnimation::Stopped) {
            animationX.setStartValue(mCard.angleX);
            animationX.setEndValue(0.0);
            animationX.start();
        }
        if (animationY.state() == QPropertyAnimation::Stopped) {
            animationY.setStartValue(mCard.angleY);
            animationY.setEndValue(0.0);
            animationY.start();
        }
    }
    update();
}

qreal RotatingCard::CardAngleX()
{
    return mCard.angleX;
    //return qreal();
}

qreal RotatingCard::CardAngleY()
{
    return mCard.angleY;
    //return qreal();
}

void RotatingCard::SetCardAngleX(qreal x)
{
    mCard.angleX = x;
    update();
}

void RotatingCard::SetCardAngleY(qreal y)
{
    mCard.angleY = y;
    update();
}
