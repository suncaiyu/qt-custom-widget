#include "ColorfulSlidingRing.h"
#include <QMouseEvent>
#include <QPainter>
#include <math.h>

const auto PI = 3.1415926;
QPoint getPos(double angle,int radius)//根据角度和半径计算在圆上的位置
{
    return QPoint(cos(angle * PI/180) * radius,sin(angle * PI/180) * radius);
}

ColorfulSlidingRing::ColorfulSlidingRing(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(300,300);
}

ColorfulSlidingRing::~ColorfulSlidingRing()
{

}

void ColorfulSlidingRing::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
     painter.setPen(Qt::transparent);

     auto rect = event->rect();
     auto centerPoint = rect.center();

     painter.translate(centerPoint);

     auto miniSize = std::min(rect.width(),rect.height());
     int radius_big = (miniSize - 80) / 2;
     int radius_small = std::max(static_cast<int>(radius_big / 4 * 3),40);
     int radius_ball = radius_small - 30;

     QPainterPath path;
     QList<QPointF> centerList;
     QList<QPolygonF> polygonList;

     for (int i = 133;i <= 405;i += 15)
     {
         auto pos1 = getPos(i,radius_small);
         auto temp = i + 3;
         auto pos2 = getPos(temp,radius_small);

         centerList << QLineF(pos1,pos2).center();

         auto pos3 = getPos(i,radius_big);
         auto pos4 = getPos(temp,radius_big);

         QPolygonF polygon;
         polygon.append(pos1);
         polygon.append(pos2);
         polygon.append(pos4);
         polygon.append(pos3);
         polygon.append(pos1);
         polygonList << polygon;
     }

     if(isPressed)
     {
         ballAngle = atan2(pressPos.y()-centerPoint.y(),pressPos.x()-centerPoint.x()); //两点之间的角度（弧度）
         ballAngle = ballAngle*(180 / PI);
         if(ballAngle < 133 &&
            (pressPos.x() - centerPoint.x()) < 0 &&
            (pressPos.y() - centerPoint.y()) > 0)
             ballAngle = 133;

         if(ballAngle > 45 && (pressPos.x() - centerPoint.x()) > 0)
             ballAngle = 45;
     }
     auto ballPos = getPos(ballAngle,radius_ball);
     path.addEllipse(ballPos, 20, 20);

     double lastValue;
     int splitIndex{-1};
     for(int i = 0;i < centerList.size();++i)
     {
         auto distance = sqrt(pow((ballPos.x() - centerList.at(i).x()),2) + pow((ballPos.y() - centerList.at(i).y()),2));
         if(i > 0)
         {
             if(distance >= lastValue && distance < miniSize * 0.33)
             {
                 splitIndex = i - 1;
                 break;
             }
             else
             {
                 lastValue = distance;
             }
         }
         else
         {
             lastValue = distance;
         }
     }
     if(splitIndex == -1)
         splitIndex = centerList.size() - 1;

     QPainterPath unselectedPath;
     for(int i = 0;i < polygonList.size();++i)
     {
         if(i <= splitIndex)
             path.addPolygon(polygonList.at(i));
         else
             unselectedPath.addPolygon(polygonList.at(i));
     }

     painter.setBrush(QGradient(QGradient::ShyRainbow));
     painter.drawPath(path);
     painter.setBrush(Qt::darkGray);
     painter.drawPath(unselectedPath);
}

void ColorfulSlidingRing::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        pressPos = event->pos();
        isPressed = true;
        update();
    }
    QWidget::mousePressEvent(event);
}

void ColorfulSlidingRing::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        isPressed = false;
        update();
    }
    QWidget::mousePressEvent(event);
}

void ColorfulSlidingRing::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressed)
    {
        pressPos = event->pos();
        update();
    }
    QWidget::mouseMoveEvent(event);
}
