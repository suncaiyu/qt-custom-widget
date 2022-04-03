#include "irregularpopupwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>

IrregularPopupWidget::IrregularPopupWidget(QWidget * parent)
    :QWidget(parent)
{
    setPalette(Qt::white);

    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0,0);
    effect->setBlurRadius(25);
    effect->setColor(Qt::black);
    setGraphicsEffect(effect);

    auto font = this->font();
    font.setPixelSize(20);
    setFont(font);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}

IrregularPopupWidget::~IrregularPopupWidget()
{
}

QSize IrregularPopupWidget::sizeHint() const
{
    if(text.isEmpty())
    {
        return QSize(200, 100);
    }
    else
    {
        auto fontMetics = this->fontMetrics();
        auto size = fontMetics.size(Qt::AlignCenter,text);
        int width = size.width();
        int height = size.height();
        switch (widgetSharpCornersPosition)
        {
            case SharpCornersPosition::left:
            case SharpCornersPosition::right:
            {
                width += SharpCornersRectWidth;
            }break;
            case SharpCornersPosition::top:
            case SharpCornersPosition::bottom:
            {
                height += SharpCornersRectHeight;
            }break;
        }
        width += 30;
        height += 30;
        return QSize(width,height);
    }
}

void IrregularPopupWidget::setWidgetSharpCornersPosition(SharpCornersPosition newWidgetSharpCornersPosition)
{
    widgetSharpCornersPosition = newWidgetSharpCornersPosition;
    update();
}

void IrregularPopupWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    const auto rect = event->rect();
    auto width = rect.width();
    auto height = rect.height();
    painter.fillRect(rect,Qt::transparent);

    QPainterPath path;
    QPolygonF polygon;
    QRect centerRect;
    switch (widgetSharpCornersPosition)
    {
        case SharpCornersPosition::left:
        {
            polygon.append(QPointF(SharpCornersRectWidth,(height - SharpCornersRectHeight) / 2));
            polygon.append(QPointF(0,(height) / 2));
            polygon.append(QPointF(SharpCornersRectWidth,(height) / 2 + SharpCornersRectHeight/2));
            centerRect = QRect(SharpCornersRectWidth-5,0,(width - SharpCornersRectWidth),height);
        }break;
        case SharpCornersPosition::right:
        {
            polygon.append(QPointF(width - SharpCornersRectWidth,(height - SharpCornersRectHeight) / 2));
            polygon.append(QPointF(width,(height) / 2));
            polygon.append(QPointF(width - SharpCornersRectWidth,(height) / 2 + SharpCornersRectHeight/2));
            centerRect = QRect(0,0,(width - SharpCornersRectWidth),height);
        }break;
        case SharpCornersPosition::top:
        {
            polygon.append(QPointF((width - SharpCornersRectWidth) / 2,SharpCornersRectHeight));
            polygon.append(QPointF((width) / 2,0));
            polygon.append(QPointF(width / 2 + SharpCornersRectWidth/2,SharpCornersRectHeight));
            centerRect = QRect(0,SharpCornersRectHeight,width,height - SharpCornersRectHeight);
        }break;
        case SharpCornersPosition::bottom:
        {
            polygon.append(QPointF((width - SharpCornersRectWidth) / 2,height - SharpCornersRectHeight));
            polygon.append(QPointF((width) / 2,height));
            polygon.append(QPointF(width / 2 + SharpCornersRectWidth/2,height - SharpCornersRectHeight));
            centerRect = QRect(0,0,width,height - SharpCornersRectHeight);
        }
    }

    painter.setBrush(backgroundColor);
    painter.setPen(Qt::transparent);
    painter.drawPolygon(polygon);
    painter.drawRoundedRect(centerRect,6,6);
    path.addPolygon(polygon);
    path.addRoundedRect(centerRect,6,6);
    painter.setClipPath(path);

    painter.setPen(Qt::white);
    painter.drawText(centerRect,Qt::AlignCenter | Qt::TextWordWrap,text);
}

void IrregularPopupWidget::setText(const QString &newText)
{
    text = newText;
}
