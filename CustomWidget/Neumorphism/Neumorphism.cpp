#include "Neumorphism.h"
#include <QMouseEvent>
#include <QPainterPath>

Neumorphism::Neumorphism(QWidget *parent) : QWidget(parent)
{
    mHoverWidget = QSharedPointer<HoverWidget>(new HoverWidget(this));
    mEffect = QSharedPointer<QGraphicsDropShadowEffect>(new QGraphicsDropShadowEffect());
    mEffect->setColor(Qt::white);
    mEffect->setOffset(-mHoverWidget->GetOffset());
    mEffect->setBlurRadius(mHoverWidget->GetBlurRadius());
    setGraphicsEffect(mEffect.get());
}

Neumorphism::~Neumorphism()
{

}

void Neumorphism::paintEvent(QPaintEvent *event)
{

}

void Neumorphism::resizeEvent(QResizeEvent *event)
{
    mHoverWidget->move(0, 0);
    mHoverWidget->setFixedSize(size());
    QWidget::resizeEvent(event);
}

void Neumorphism::mousePressEvent(QMouseEvent *event)
{
    QPainterPath pp;
    pp.addRoundedRect(mHoverWidget->GetContentRect(), mHoverWidget->GetRadius(), mHoverWidget->GetRadius());
    if (pp.contains(event->pos())) {
        SetFlat(!mHoverWidget->GetFlat());
        update();
    }
}
