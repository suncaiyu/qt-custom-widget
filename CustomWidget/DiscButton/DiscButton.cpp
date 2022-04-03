#include "DiscButton.h"
#include <QPainter>
#include <QPainterPath>
#include <math.h>
#include <QMouseEvent>

DiscButton::DiscButton(QWidget *parent) : QWidget(parent)
{

}

DiscButton::~DiscButton()
{

}

void DiscButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    QPoint centerPoint = rect().center();

    painter.save();
    painter.setPen(QColor("#222222"));
    painter.setBrush(QColor("#EAEAEA"));
    double radius = (std::min(width(),height()) - 10 * 2 ) / 2;
    drawRect = QRectF(centerPoint.x()-radius, centerPoint.y()-radius, radius*2, radius*2);
    double arcHeight = radius / 2;

    fanShaped[0] = gradientArc(45.0,  90.0, arcHeight);//上
    fanShaped[1] = gradientArc(135.0, 90.0, arcHeight);//左
    fanShaped[2] = gradientArc(225.0, 90.0, arcHeight);//下
    fanShaped[3] = gradientArc(315.0, 90.0, arcHeight);//右

    for (int i = 0;i < 4;++i)
    {
        painter.drawPath(fanShaped[i]);
    }
    painter.restore();

    centerCircularRect = QRectF(centerPoint.x() - (radius / 2), centerPoint.y() - (radius / 2), radius, radius).adjusted(2,2,-2,-2);
    painter.save();
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor("#EAEAEA"));
    painter.drawEllipse(centerCircularRect);
    painter.restore();

    //绘制文字
    //左
    painter.save();
    QRectF textRect = QRectF(drawRect.x(),centerCircularRect.y(),radius / 2,radius);
    QPen p(Qt::SolidLine);
    p.setColor("#000000");
    p.setWidth(2);
    painter.setPen(p);
    QFont font = painter.font();
    font.setPixelSize(24);
    painter.setFont(font);
    painter.drawText(textRect, Qt::AlignCenter, "〈");//在此区域的中间位置绘制文字 〉

    //上
    textRect = QRectF(centerCircularRect.x(),drawRect.y(),radius,radius / 2);
    painter.drawText(textRect, Qt::AlignCenter, "︿");

    //右
    textRect = QRectF(centerCircularRect.topRight().x(),centerCircularRect.topRight().y(),radius / 2,radius);
    painter.drawText(textRect, Qt::AlignCenter, "〉");

    //下
    textRect = QRectF(centerCircularRect.bottomLeft().x(),centerCircularRect.bottomLeft().y(),radius,radius / 2);
    painter.drawText(textRect, Qt::AlignCenter, "﹀");

    painter.drawText(centerCircularRect, Qt::AlignCenter, "OK");
    painter.restore();

    if(pressedBtn != pressBtnType::None)
    {
        painter.save();
        QColor slightlyOpaqueBlack(0, 0, 0, 63);
        painter.setBrush(slightlyOpaqueBlack);
        painter.setPen(Qt::transparent);
        if(pressedBtn == pressBtnType::center)
        {
            painter.drawEllipse(centerCircularRect);
        }
        else
        {
            int index = -1;
            index = static_cast<int>(pressedBtn);
            if(index >= 0)
            {
                painter.drawPath(fanShaped[index]);
            }
        }
        painter.restore();
    }

    painter.restore();
}

void DiscButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
     {
         QPoint point = event->pos();
         if(isPointInCir(point,drawRect.toRect()))
         {
             if(isPointInCir(point,centerCircularRect.toRect()))
             {
                 pressedBtn = pressBtnType::center;
             }
             else
             {
                 QPoint centerPoint = drawRect.toRect().center();
                 double angle = atan2(point.y()-centerPoint.y(),point.x()-centerPoint.x()); //两点之间的角度（弧度）
                 angle = -angle*(180 / 3.1415926); //0°~180° - -180°~0°
                 if(angle < 0.0)
                 {
                     angle = 360.0 - abs(angle);
                 }
                 if(angle < 45.0 || angle > 315.0)
                 {
                     pressedBtn = pressBtnType::right;
                 }
                 else if(angle >= 45.0 && angle < 135.0)
                 {
                     pressedBtn = pressBtnType::up;
                 }
                 else if(angle >= 135.0 && angle < 225.0)
                 {
                     pressedBtn = pressBtnType::left;
                 }
                 else if(angle >= 225.0 && angle < 315.0)
                 {
                     pressedBtn = pressBtnType::down;
                 }
             }
             update();
         }
     }
     return QWidget::mousePressEvent(event);
}

void DiscButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(pressedBtn != pressBtnType::None)
    {
        pressedBtn = pressBtnType::None;
        update();
    }
    return QWidget::mouseReleaseEvent(event);
}

bool DiscButton::isPointInCir(const QPoint &point, const QRect &rect)
{
    const QPoint & centerPoint = rect.center();
    int x = point.x() - centerPoint.x();
    int y = point.y() - centerPoint.y();
    if(sqrt(pow(x,2) + pow(y,2)) <= static_cast<double>(rect.width() / 2))
    {
        return true;
    }
    return false;
}

QPainterPath DiscButton::gradientArc(double startAngle, double angleLength, double arcHeight)
{

    QPainterPath path;
    path.moveTo(drawRect.center());
    path.arcTo(drawRect, startAngle, angleLength);

    QPainterPath subPath;
    subPath.addEllipse(drawRect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    // path为扇形 subPath为椭圆
    path -= subPath;
    return path;
}
