#include "SPushButton.h"
#include <QDebug>
#include <QPainter>

SPushButton::SPushButton(QWidget *parent):QPushButton(parent)
{
    //39 41 45    0,177,234
    x1 = 39;
    x2 = 41;
    x3 = 45;
    m_enteranimation = new QPropertyAnimation(this, "x1");
    m_enteranimation2 = new QPropertyAnimation(this, "x2");
    m_enteranimation3 = new QPropertyAnimation(this, "x3");
    m_leaveanimation = new QPropertyAnimation(this, "x1");
    m_leaveanimation2 = new QPropertyAnimation(this, "x2");
    m_leaveanimation3 = new QPropertyAnimation(this, "x3");

    connect(this, SIGNAL(XChange()),this,SLOT(Printf()));
}

SPushButton::~SPushButton() {}

int SPushButton::GetX1()
{
    return x1;
}

void SPushButton::SetX1(int xx1)
{
    x1 = xx1;
    update();
}
int SPushButton::GetX2()
{
    return x2;
}

void SPushButton::SetX2(int xx1)
{
    x2 = xx1;
    update();
}
int SPushButton::GetX3()
{
    return x3;
}

void SPushButton::SetX3(int xx1)
{
    x3 = xx1;
    update();
}

void SPushButton::Printf()
{
    qDebug() << x1;
}

void SPushButton::enterEvent(QEvent *)

{
    m_enteranimation->setDuration(1000);
    m_enteranimation->setStartValue(x1);
    m_enteranimation->setEndValue(0);
    m_enteranimation->setEasingCurve(QEasingCurve::OutExpo);

    m_enteranimation2->setDuration(1000);
    m_enteranimation2->setStartValue(x2);
    m_enteranimation2->setEndValue(177);
    m_enteranimation2->setEasingCurve(QEasingCurve::OutExpo);


    m_enteranimation3->setDuration(1000);
    m_enteranimation3->setStartValue(x3);
    m_enteranimation3->setEndValue(234);
    m_enteranimation3->setEasingCurve(QEasingCurve::OutExpo);

    if (m_leaveanimation->Running) {
        m_leaveanimation->stop();
    }
    if (m_leaveanimation2->Running) {
        m_leaveanimation2->stop();
    }
    if (m_leaveanimation3->Running) {
        m_leaveanimation3->stop();
    }
    m_enteranimation->start();
    m_enteranimation2->start();
    m_enteranimation3->start();
}

void SPushButton::leaveEvent(QEvent *)
{
    m_leaveanimation->setDuration(1000);
    m_leaveanimation->setStartValue(x1);
    m_leaveanimation->setEndValue(39);

    m_leaveanimation2->setDuration(1000);
    m_leaveanimation2->setStartValue(x2);
    m_leaveanimation2->setEndValue(41);

    m_leaveanimation3->setDuration(1000);
    m_leaveanimation3->setStartValue(x3);
    m_leaveanimation3->setEndValue(45);


    if (m_enteranimation->Running) {
        m_enteranimation->stop();
    }
    if (m_enteranimation2->Running) {
        m_enteranimation2->stop();
    }
    if (m_enteranimation3->Running) {
        m_enteranimation3->stop();
    }
    m_leaveanimation->start();
    m_leaveanimation2->start();
    m_leaveanimation3->start();
}

void SPushButton::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QRect r = rect();
    r.adjust(0, 0, -1, -1);

    paint.fillRect(rect(), QBrush(QColor(x1, x2, x3)));
     paint.drawRect(r);
    //    QFont font("宋体", 15);
    //    paint.setFont(font);
    //    paint.setPen(Qt::black);
    //    paint.drawText(10,10, "wocao");
    paint.end();

}
