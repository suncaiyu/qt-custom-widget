#include "dragsliderverify.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

DragSliderVerify::DragSliderVerify(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);
    setMouseTracking(true);
}

DragSliderVerify::~DragSliderVerify()
{
}

void DragSliderVerify::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::transparent);

    auto rect = event->rect();
    if(verifyState == State::Verified)
    {
        painter.fillRect(rect,QColor("#7AC23C"));
    }
    else
    {
        painter.fillRect(rect,QColor("#E8E8E8"));
    }

    auto font = painter.font();
    font.setPixelSize(16);
    painter.setFont(font);

    if(verifyState == State::Verified)
    {
        painter.setPen(Qt::white);
        painter.drawText(rect,Qt::AlignCenter,"验证通过");

        sliderRect = QRect(rect.width() - 35,0,35,30);
        painter.fillRect(sliderRect,Qt::white);
        QPainterPath path;
        path.addEllipse(sliderRect.center(),7,7);
        painter.fillPath(path,QColor("#7AC23C"));
        auto pathRect = path.boundingRect();
        painter.setPen(QPen(Qt::white,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        painter.drawLine(QPoint(pathRect.x() + 4,14),QPoint(pathRect.x() + 6,17));
        painter.drawLine(QPoint(pathRect.x() + 6,17),QPoint(pathRect.x() + 10,11));
    }
    else
    {
        painter.setPen(QColor("#C0C0C0"));
        painter.fillRect(QRect(0,0,sliderX,30),QColor("#7AC23C"));
        painter.setBrush(Qt::white);

        painter.save();
        QPainterPath textRectPath;
        textRectPath.addRect(QRect(0,0,sliderX,30));
        painter.setClipPath(textRectPath);
        painter.setPen(Qt::white);
        painter.drawText(rect,Qt::AlignCenter,"拖动滑块验证");
        painter.restore();

        painter.save();
        textRectPath.clear();
        textRectPath.addRect(QRect(sliderX + 30,0,rect.width() - sliderX - 30,30));
        painter.setClipPath(textRectPath);
        painter.setPen(Qt::black);
        painter.drawText(rect,Qt::AlignCenter,"拖动滑块验证");
        painter.restore();

        sliderRect = QRect(sliderX,0,35,30);
        painter.drawRect(sliderRect);

        painter.setPen(QPen(QColor("#C0C0C0"),2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

        painter.drawLine(QPoint(sliderX + 10,10),QPoint(sliderX + 15,15));
        painter.drawLine(QPoint(sliderX + 15,15),QPoint(sliderX + 10,20));

        painter.drawLine(QPoint(sliderX + 20,10),QPoint(sliderX + 25,15));
        painter.drawLine(QPoint(sliderX + 25,15),QPoint(sliderX + 20,20));
    }
}

void DragSliderVerify::mousePressEvent(QMouseEvent *event)
{
    if(verifyState == State::Unverified)
    {
        if(sliderRect.contains(event->pos()))
        {
            verifyState = State::Verifying;
        }
    }
    QWidget::mousePressEvent(event);
}

void DragSliderVerify::mouseReleaseEvent(QMouseEvent* event)
{
    if(verifyState == State::Verifying)
    {
        verifyState = State::Unverified;
        setCursor(Qt::ArrowCursor);
        sliderX = 0;
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void DragSliderVerify::mouseMoveEvent(QMouseEvent *event)
{
    if(sliderRect.contains(event->pos()))
    {
        if(verifyState != State::Verified)
        {
            setCursor(Qt::SizeAllCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }

    if(verifyState == State::Verifying)
    {
        auto posX = event->pos().x();
        sliderX = std::max(posX - sliderRect.width()/2,0);
        if(sliderX >= (rect().width() - sliderRect.width()))
        {
            setCursor(Qt::SizeAllCursor);
            verifyState = State::Verified;
        }
        update();
    }
    QWidget::mouseMoveEvent(event);
}
