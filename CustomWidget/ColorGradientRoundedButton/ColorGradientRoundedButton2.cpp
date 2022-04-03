#include "ColorGradientRoundedButton2.h"
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QPainterPath>
#include <QRandomGenerator>

QColor getRandomColor()
{
    return QColor(QRandomGenerator::global()->bounded(255),
                  QRandomGenerator::global()->bounded(255),
                  QRandomGenerator::global()->bounded(255));
}

ColorGradientRoundedButton2::ColorGradientRoundedButton2(QWidget *parent)
    : QAbstractButton(parent)
{
    startColor = doubleColor(getRandomColor(),getRandomColor());
    endColor = doubleColor(getRandomColor(),getRandomColor());

    this->setMinimumSize(180,50);
    setMouseTracking(true);

    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(this);
    setGraphicsEffect(effect);
    effect->setOffset(0,0);
    effect->setBlurRadius(25);
    effect->setColor(Qt::black);

    timer.setInterval(40);
    connect(&timer,&QTimer::timeout,this,&ColorGradientRoundedButton2::onTimer);
}

ColorGradientRoundedButton2::~ColorGradientRoundedButton2()
{
}

void ColorGradientRoundedButton2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    auto rect = event->rect();
    auto rectWidth = rect.width();

    QPainterPath path;
    path.addRoundedRect(rect,25,25);
    painter.setClipPath(path);
    painter.drawRect(rect);

    QLinearGradient linearGradient1(QPoint(-rectX,0),QPoint(rectWidth - rectX,0));
    linearGradient1.setColorAt(0,startColor.fristColor);
    linearGradient1.setColorAt(1,startColor.secondColor);
    painter.fillRect(QRect(-rectX,0,rectWidth,rect.height()),linearGradient1);

    QLinearGradient linearGradient2(QPoint(rectWidth - rectX,0),QPoint(rectWidth * 2 - rectX,0));
    linearGradient2.setColorAt(0,endColor.fristColor);
    linearGradient2.setColorAt(1,endColor.secondColor);
    painter.fillRect(QRect(rectWidth - rectX,0,rectWidth,rect.height()),linearGradient2);

    auto font = painter.font();
    font.setBold(true);
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(rect,Qt::AlignCenter,text());
}

void ColorGradientRoundedButton2::onTimer()
{
    if(rectXChangeModel == ChangeModel::Plus)
    {
        rectX += (rect().width() / 6);
        if(rectX >= rect().width())
        {
            rectX = rect().width();
            timer.stop();
        }
    }
    else
    {
        rectX -= (rect().width() / 6);
        if(rectX <= 0)
        {
            rectX = 0;
            timer.stop();
        }
    }
    update();
}

void ColorGradientRoundedButton2::enterEvent(QEvent *event)
{
    if(timer.isActive())
        timer.stop();
    rectXChangeModel = ChangeModel::Plus;
    timer.start();
    QWidget::enterEvent(event);
}

void ColorGradientRoundedButton2::leaveEvent(QEvent *event)
{
    if(timer.isActive())
        timer.stop();
    rectXChangeModel = ChangeModel::Minus;
    timer.start();
    QWidget::leaveEvent(event);
}
