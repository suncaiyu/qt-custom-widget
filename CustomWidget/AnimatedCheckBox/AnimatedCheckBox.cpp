#include "AnimatedCheckBox.h"
#include <QLabel>
#include <QGraphicsOpacityEffect>
#include <QApplication>
#include <QPropertyAnimation>
#include <QStyle>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>

AnimatedCheckBox::AnimatedCheckBox(QWidget *parent) : QCheckBox(parent)
{
    mIndicator = std::make_shared<QLabel>(this);

    this->setMinimumHeight(30);
    this->setContentsMargins(2, 2, 2, 2);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setProperty("class", "AnimatedCheckBox");
    mIndicator->setProperty("class", "AnimatedCheckBoxIndicator");

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.9);
    mIndicator->setGraphicsEffect(effect);

    qApp->setStyleSheet(R"(
                        .AnimatedCheckBox[checked=true ] { background: rgb(0,137,231) }
                        .AnimatedCheckBox[checked=false] { background: gray }
                        .AnimatedCheckBoxIndicator { background: rgb(240,240,240) })");

    QPropertyAnimation *animation = new QPropertyAnimation(mIndicator.get(), "pos", this);
    connect(this, &QCheckBox::toggled, [=] {
        int b = this->contentsMargins().left();
        int x = this->isChecked() ? this->width() - mIndicator->width() - b : b;
        int y = b;

        animation->stop();
        animation->setDuration(200);
        animation->setEndValue(QPoint(x, y));
        animation->setEasingCurve(QEasingCurve::InOutCubic);
        animation->start();

        this->style()->polish(this);
    });
}

AnimatedCheckBox::~AnimatedCheckBox()
{

}

void AnimatedCheckBox::paintEvent(QPaintEvent *event)
{
//    QCheckBox::paintEvent(event);
}

void AnimatedCheckBox::resizeEvent(QResizeEvent *event)
{
    qDebug() << event->size();
    int b = this->contentsMargins().left();
    int x = this->isChecked() ? this->width() - mIndicator->width() - b : b;
    int y = b;
    int w = height() - b - b;
    int h = w;
    mIndicator->setGeometry(x, y, w, h);

    this->setMinimumWidth(height() * 2);

    this->setStyleSheet(QString(".AnimatedCheckBox { border-radius: %1px } .AnimatedCheckBoxIndicator { border-radius: %2px }")
                        .arg(this->height() / 2)
                        .arg(mIndicator->height() / 2));
    QCheckBox::resizeEvent(event);
}

void AnimatedCheckBox::mousePressEvent(QMouseEvent *event)
{
//    event->accept();
    setChecked(!isChecked());
}

QSize AnimatedCheckBox::sizeHint() const
{
    return QSize(100, 50);
}
