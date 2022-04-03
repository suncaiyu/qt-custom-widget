#include "PlayStateControl.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QDebug>

PlayStateControl::PlayStateControl(QWidget *parent)
    : QWidget(parent)
{
    setPalette(Qt::white);
    diskPixmap.load(":/img/mediaDisk.png");
    polePixmap.load(":/img/Pole.png");
    centerPixmap.load(":/img/F4.jpeg");
    setMinimumSize(300,250);

    connect(&angleTimer,&QTimer::timeout,[this]
    {
        angle += 1.0;
        if(angle == 360.0)
            angle = 0.0;
        update();
    });
    angleTimer.setInterval(40);

    connect(&poleSpinTimer,&QTimer::timeout,[this]
    {
        if(isPlaying)
        {
            poleSpinAngle -= 1.0;
            if(poleSpinAngle == 0.0)
            {
                poleSpinTimer.stop();
            }

        }
        else
        {
            poleSpinAngle += 1.0;
            if(poleSpinAngle > 25.0)
            {
                poleSpinTimer.stop();
            }
        }
        update();
    });
    poleSpinTimer.setInterval(20);
}

PlayStateControl::~PlayStateControl()
{
}

void PlayStateControl::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    const auto rect = event->rect();
    auto radius = std::min(rect.width(),rect.height()) / 2 - 25;
    QRect rectangle(-radius,-radius,radius * 2,radius * 2);

    painter.translate(rect.center());
    painter.setPen(Qt::transparent);

    painter.drawPixmap(rectangle,diskPixmap);


    auto centerImgRadius = radius / 1.6;
    auto centerImgRect = QRect(-centerImgRadius, -centerImgRadius, centerImgRadius*2, centerImgRadius*2);

    painter.save();
    QRegion maskedRegion(centerImgRect, QRegion::Ellipse);
    painter.setClipRegion(maskedRegion);
    painter.rotate(angle);
    painter.drawPixmap(centerImgRect,centerPixmap);
    painter.restore();

    auto poleRect = QRect(rectangle.topRight().x(),rectangle.topRight().y(),rect.width()*0.15,rect.height()*0.5);
    auto polePixmapTemp = polePixmap.scaled(poleRect.size(),Qt::KeepAspectRatio);
    auto difference = polePixmapTemp.width() + radius - (rect.width()/2);
    if(difference > 0)
    {
        poleRect.setX(poleRect.x() - difference);
    }

    painter.save();
    painter.translate(poleRect.topLeft());
    painter.rotate(poleSpinAngle);
    painter.drawPixmap(QPoint(0,0),polePixmapTemp);
    painter.restore();
}

void PlayStateControl::mousePressEvent(QMouseEvent *event)
{
    isPlaying = !isPlaying;
    poleIsSpin = true;
    poleSpinTimer.start();
    if(isPlaying)
    {
        angleTimer.stop();
    }
    else
    {
        angleTimer.start();
    }
    QWidget::mousePressEvent(event);
}
