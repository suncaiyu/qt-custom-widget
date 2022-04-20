#include "HoverWidget.h"
#include <QPainter>

HoverWidget::HoverWidget(QWidget *parent) : QWidget(parent)
{
    mEffect = QSharedPointer<QGraphicsDropShadowEffect>(new QGraphicsDropShadowEffect());
    mEffect->setColor(QColor(200, 200, 200));
    mEffect->setOffset(mOffset);
    mEffect->setBlurRadius(mBlurRadius);
    setGraphicsEffect(mEffect.get());
}

HoverWidget::~HoverWidget()
{

}

void HoverWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    p.setPen(Qt::NoPen);
    if (mFlat) {
        p.setBrush(QColor(235, 235, 235));
        mText = "UnPressed";
    } else {
        QLinearGradient lg(mContentRect.x(), mContentRect.y(), mContentRect.x() + mContentRect.width(), mContentRect.y() + mContentRect.height());
        lg.setColorAt(0, QColor(216, 216, 216));
        lg.setColorAt(1, QColor(250, 250, 250));
        p.setBrush(lg);
        mText = "Pressed";
    }
    p.drawRoundedRect(mContentRect, mRadius, mRadius);
    QPen pen;
    pen.setColor(Qt::lightGray);
    QFont font = p.font();
    font.setFamily("Microsoft YaHei");
    font.setPixelSize(mContentRect.width() / 7);
    p.setFont(font);
    p.setPen(pen);
    p.drawText(mContentRect, Qt::AlignCenter, mText);
}

void HoverWidget::resizeEvent(QResizeEvent *event)
{
    if (width() < height()) {
        int distance = height() - width();
        mContentRect = rect().adjusted(mMargin, mMargin + distance / 2, -mMargin, -mMargin - distance / 2);
    } else {
        int distance = -height() + width();
        mContentRect = rect().adjusted(mMargin + distance / 2, mMargin , -mMargin - distance / 2, -mMargin);
    }
    QWidget::resizeEvent(event);
}
