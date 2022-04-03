#include "ColorGradientRoundedButton1.h"
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPainterPath>
#include <QRandomGenerator>

QVariant myColorInterpolator(const doubleColor1 &start, const doubleColor1 &end, qreal progress)
{
    auto fr = start.fristColor.red() + ((end.fristColor.red() - start.fristColor.red()) * progress);
    auto fg = start.fristColor.green() + ((end.fristColor.green() - start.fristColor.green()) * progress);
    auto fb = start.fristColor.blue() + ((end.fristColor.blue() - start.fristColor.blue()) * progress);

    auto sr = start.secondColor.red() + ((end.secondColor.red() - start.secondColor.red()) * progress);
    auto sg = start.secondColor.green() + ((end.secondColor.green() - start.secondColor.green()) * progress);
    auto sb = start.secondColor.blue() + ((end.secondColor.blue() - start.secondColor.blue()) * progress);

    return QVariant::fromValue(doubleColor1(QColor(fr,fg,fb),QColor(sr,sg,sb)));
}

QColor getRandomColor1()
{
    return QColor(QRandomGenerator::global()->bounded(255),
                  QRandomGenerator::global()->bounded(255),
                  QRandomGenerator::global()->bounded(255));
}

ColorGradientRoundedButton1::ColorGradientRoundedButton1(QWidget *parent)
    : QAbstractButton(parent)
{
    qRegisterAnimationInterpolator<doubleColor1>(myColorInterpolator);

    startColor = doubleColor1(getRandomColor1(),getRandomColor1());
    endColor = doubleColor1(getRandomColor1(),getRandomColor1());
    currentColor = startColor;

    this->setMinimumSize(180,50);
    setMouseTracking(true);

    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
    setGraphicsEffect(effect);
    effect->setOffset(0,0);
    effect->setBlurRadius(25);
    effect->setColor(Qt::black);

    animation = new QPropertyAnimation(this, "currentColor");
    animation->setDuration(400);
    connect(animation,&QPropertyAnimation::valueChanged,this,&ColorGradientRoundedButton1::onValueChanged);
}

ColorGradientRoundedButton1::~ColorGradientRoundedButton1()
{
}

void ColorGradientRoundedButton1::onValueChanged(const QVariant &value)
{
    update();
}

void ColorGradientRoundedButton1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    auto rect = event->rect();

    QPainterPath path;
    path.addRoundedRect(rect,25,25);
    painter.setClipPath(path);
    painter.drawRect(rect);

    QLinearGradient linearGradient(rect.topLeft(),rect.topRight());
    linearGradient.setColorAt(0,currentColor.fristColor);
    linearGradient.setColorAt(1,currentColor.secondColor);
    painter.fillRect(rect,linearGradient);

    auto font = painter.font();
    font.setBold(true);
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(rect,Qt::AlignCenter,text());
}

void ColorGradientRoundedButton1::enterEvent(QEvent *event)
{
    if(animation->state() == QAbstractAnimation::Running)
    {
        animation->stop();
    }
    animation->setStartValue(QVariant::fromValue(currentColor));
    animation->setEndValue(QVariant::fromValue(endColor));
    animation->start();

    QWidget::enterEvent(event);
}

void ColorGradientRoundedButton1::leaveEvent(QEvent *event)
{
    if(animation->state() == QAbstractAnimation::Running)
    {
        animation->stop();
    }
    animation->setStartValue(QVariant::fromValue(currentColor));
    animation->setEndValue(QVariant::fromValue(startColor));
    animation->start();

    QWidget::leaveEvent(event);
}
