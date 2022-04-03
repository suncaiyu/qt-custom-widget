#include "roundmmenuinupperleftcornerwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

RoundMmenuInUpperLeftCornerWidget::RoundMmenuInUpperLeftCornerWidget(QWidget *parent)
    : QWidget(parent)
{
    setPalette(Qt::white);
    setMouseTracking(true);

    connect(&timer,&QTimer::timeout,this,&RoundMmenuInUpperLeftCornerWidget::onTimer);
    timer.setInterval(40);

    imgList << QPixmap(":/img/F1.jpeg");
    imgList << QPixmap(":/img/F2.jpeg");
    imgList << QPixmap(":/img/F3.jpeg");
    imgList << QPixmap(":/img/F4.jpeg");
    imgList << QPixmap(":/img/F5.jpeg");
    imgList << QPixmap(":/img/F6.jpeg");
    imgList << QPixmap(":/img/F7.jpeg");
    imgList << QPixmap(":/img/F8.jpeg");
    imgList << QPixmap(":/img/F9.jpeg");
    imgList << QPixmap(":/img/F10.jpeg");
    imgList << QPixmap(":/img/F11.jpeg");
    imgList << QPixmap(":/img/F12.jpeg");

    auto it = std::inserter(menuRectList,menuRectList.begin());
    for(int i = 0;i < imgList.size();++i,++it)
    {
        *it = QRect();
    }
}

RoundMmenuInUpperLeftCornerWidget::~RoundMmenuInUpperLeftCornerWidget()
{
}

void RoundMmenuInUpperLeftCornerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    const auto rect = event->rect();

    auto width = rect.width();
    auto height = rect.height();
    Length = std::min(width,height);
    if(widgetState == State::Shrink)
    {
        radius = 0.33 * Length / 1.2;
    }

    auto ellipseCenter = QPointF(radius*0.2,radius*0.2);
    painter.save();
    QRadialGradient radialGradient;
    radialGradient.setCenter(ellipseCenter);
    radialGradient.setRadius(radius * 1.2);
    radialGradient.setFocalPoint(ellipseCenter);
    radialGradient.setColorAt(0.0,QColor("#EAEAEA"));
    radialGradient.setColorAt(1.0,QColor("#AFAFAF"));
    painter.setBrush(radialGradient);
    painter.setPen(QColor("#808080"));
    painter.drawEllipse(ellipseCenter,radius,radius);
    painter.restore();

    homeBtnRect = QRect(radius*0.05,radius*0.05,radius*0.8,radius*0.8);
    painter.drawPixmap(homeBtnRect,QPixmap(":/img/home.png"));

    if(widgetState != State::Shrink)
    {
        QPainterPath p1;
        p1.addEllipse(ellipseCenter,outSideRadius,outSideRadius);
        QPainterPath p2;
        p2.addEllipse(ellipseCenter,radius,radius);
        arcAreaPath = p1 - p2;

        painter.setBrush(QColor("#E2E2D0"));
        painter.setPen(Qt::transparent);
        painter.drawPath(arcAreaPath);
    }

    if(widgetState != State::Shrink)
    {
        int cha = outSideRadius  - radius;
        int imgX = (1.2 * radius) + (cha - radius*0.8) / 2;
        int imgY = 0.2 *radius;

        QRect imgRect;
        if(widgetState == State::Popping)
            imgRect = QRect(imgX,imgY,cha * 0.6,cha * 0.6);
        else
            imgRect = QRect(imgX,imgY,radius*0.8,radius*0.8);

        int size = imgList.size();
        QTransform transform;
        QPoint temp(static_cast<int>(radius*0.4),static_cast<int>(radius*0.4));
        for (int i = 0;i < size;++i)
        {
            auto angle = 360 / size * i + allBeforeAngleOffset + currentOffset;
            painter.save();
            painter.rotate(angle);
            painter.drawPixmap(imgRect,imgList.at(i));
            painter.restore();

            transform.reset();
            transform.rotate(angle);
            QPoint transform_p = transform.map(imgRect.center());
            menuRectList[i] = QRect(transform_p - temp,transform_p + temp);
        }

        if(pressIndexInMenuRectList >= 0)
        {
            QColor slightlyOpaqueBlack(0, 0, 0, 63);
            painter.setBrush(slightlyOpaqueBlack);
            painter.drawEllipse(menuRectList.at(pressIndexInMenuRectList));
        }
    }
}

void RoundMmenuInUpperLeftCornerWidget::mousePressEvent(QMouseEvent *event)
{
    QRegion ellipseRegion(homeBtnRect, QRegion::Ellipse);
    auto pos = event->pos();
    if(ellipseRegion.contains(pos))
    {
        if(widgetState == State::Shrink)
        {
            lastWidgetState = State::Shrink;
            radius = 0.5 * Length / 1.2;
            outSideRadius = radius;
            widgetState = State::Popping;
        }
        else if(widgetState == State::Popped)
        {
            lastWidgetState = State::Popped;
            radius = 0.33 * Length / 1.2;
            widgetState = State::Popping;
        }
        timer.start();
    }
    else
    {
        pressIndexInMenuRectList = -1;
        if(widgetState == State::Popped)
        {
            for(int i = 0;i < menuRectList.size();++i)
            {
                if(menuRectList.at(i).contains(pos))
                {
                    pressIndexInMenuRectList = i;
                    break;
                }
            }

            if(pressIndexInMenuRectList == -1)
            {
                if(arcAreaPath.contains(pos))
                {
                    pressPos = pos;
                    setCursor(Qt::OpenHandCursor);
                }
            }
        }
    }
    update();

    QWidget::mousePressEvent(event);
}

void RoundMmenuInUpperLeftCornerWidget::onTimer()
{
    if(widgetState == State::Popping)
    {
        if(lastWidgetState == State::Shrink)
        {
            outSideRadius += Length * 0.1;
            if(outSideRadius >= (Length - radius * 0.2))
            {
                timer.stop();
                widgetState = State::Popped;
                outSideRadius = Length - radius * 0.2;
            }
        }
        else if(lastWidgetState == State::Popped)
        {
            outSideRadius -= Length * 0.1;
            if(outSideRadius < radius)
            {
                timer.stop();
                widgetState = State::Shrink;
                outSideRadius = radius;
            }
        }
        update();
    }
}

void RoundMmenuInUpperLeftCornerWidget::resizeEvent(QResizeEvent *event)
{
    widgetState = State::Shrink;

    update();
    QWidget::resizeEvent(event);
}

void RoundMmenuInUpperLeftCornerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(widgetState == State::Popped)
    {
        pressIndexInMenuRectList = -1;
        pressPos = QPoint(0,0);
        allBeforeAngleOffset += currentOffset;
        currentOffset = 0;
        setCursor(Qt::ArrowCursor);
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void RoundMmenuInUpperLeftCornerWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    bool mouseInAbtnZone{false};
    QRegion ellipseRegion(homeBtnRect, QRegion::Ellipse);

    if(ellipseRegion.contains(pos))
    {
        mouseInAbtnZone = true;
    }
    else
    {
        if(widgetState == State::Popped)
        {
            for(const auto & rect : menuRectList)
            {
                QRegion ellipseRegion(rect, QRegion::Ellipse);
                if(ellipseRegion.contains(pos))
                {
                    mouseInAbtnZone = true;
                    break;
                }
            }
        }
    }

    if(pressPos.isNull())
    {
        setCursor(mouseInAbtnZone ? Qt::PointingHandCursor : Qt::ArrowCursor);
    }
    else
    {
        QLineF line1(QPoint(radius*0.2,radius*0.2),pressPos);
        QLineF line2(QPoint(radius*0.2,radius*0.2),pos);
        int angle = line2.angleTo(line1);
        if(angle > 200)
        {
            if(pos.x() > 0 && pos.y() > 0)
            {
                angle = -(360 - angle);
            }
        }

        currentOffset = angle;
        setCursor(Qt::OpenHandCursor);
        update();
    }

    QWidget::mouseMoveEvent(event);
}
