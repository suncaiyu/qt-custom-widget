#include "InnerWidget.h"
#include <QPainter>
#include <QDebug>
#include <QPainterPath>

InnerWidget::InnerWidget(QWidget *parent) : QWidget(parent)
{
    mTargetColor = QColor (235, 235, 235);
    mShadowDark = QColor(50, 50, 50, 50);
    mShadowLight = Qt::white;
}

InnerWidget::~InnerWidget()
{

}

void InnerWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    p.setPen(Qt::NoPen);

    DrawLeftTop(p);
    DrawRightBottom(p);
    DrawLeftBottom(p);
    DrawRightTop(p);

    QRect tmpRect = rect().adjusted(mShadowLength, mShadowLength, -mShadowLength, -mShadowLength);
    p.setBrush(mTargetColor);
    p.setClipping(false);
    p.drawRoundedRect(tmpRect, mRadius, mRadius);
}

void InnerWidget::DrawLeftTop(QPainter &p)
{
    QPainterPath clipPath1;
    clipPath1.moveTo(rect().x(), rect().y());
    clipPath1.lineTo(rect().x() + rect().width(), rect().y());
    clipPath1.lineTo(rect().x(), rect().y() + rect().height());
    clipPath1.closeSubpath();
    p.setClipPath(clipPath1);
    for (int i = 0; i < mShadowLength; ++i) {
        QColor color = mShadowDark;
        color.setAlpha(color.alpha() - (color.alpha() / mShadowLength) * i);
        QRect tmpRect = rect().adjusted(i, i, -i, -i);
        p.setBrush(mTargetColor);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
        p.setBrush(color);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
    }
}

void InnerWidget::DrawRightBottom(QPainter &p)
{
    QPainterPath clipPath;
    clipPath.moveTo(rect().x() + rect().width(), rect().y() + rect().height());
    clipPath.lineTo(rect().x(), rect().y() + rect().height());
    clipPath.lineTo(rect().x() + rect().width(), rect().y());
    clipPath.closeSubpath();
    p.setClipPath(clipPath);
    for (int i = 0; i < mShadowLength; ++i) {
        QColor color = mShadowLight;
        int perRed = (mShadowLight.red() - mTargetColor.red()) / mShadowLength;
        color.setRed(color.red() - i * perRed);
        int perGreen = (mShadowLight.green() - mTargetColor.green()) / mShadowLength;
        color.setGreen(color.green() - i * perGreen);
        int perBlue = (mShadowLight.blue() - mTargetColor.blue()) / mShadowLength;
        color.setBlue(color.blue() - i * perBlue);
        QRect tmpRect = rect().adjusted(i, i, -i, -i);
        p.setBrush(color);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
    }
}

void InnerWidget::DrawLeftBottom(QPainter &p)
{
    QPainterPath clipPath;
    QRect leftBottom(rect().x(), rect().y() + rect().height() - mRadius, mRadius, mRadius);
    clipPath.addRect(leftBottom);
    p.setClipPath(clipPath);
    QLinearGradient lg(leftBottom.x(), leftBottom.y(), leftBottom.x() + leftBottom.width(), leftBottom.y() + leftBottom.height());
    for (int i = 0; i < mShadowLength; ++i) {
        QColor startColor = mShadowDark;
        startColor.setAlpha(startColor.alpha() - (startColor.alpha() / mShadowLength) * i);
        QColor endColor = mShadowLight;
        int perRed = (mShadowLight.red() - mTargetColor.red()) / mShadowLength;
        endColor.setRed(endColor.red() - i * perRed);
        int perGreen = (mShadowLight.green() - mTargetColor.green()) / mShadowLength;
        endColor.setGreen(endColor.green() - i * perGreen);
        int perBlue = (mShadowLight.blue() - mTargetColor.blue()) / mShadowLength;
        endColor.setBlue(endColor.blue() - i * perBlue);
        lg.setColorAt(0, startColor);
        lg.setColorAt(1, endColor);
        p.setBrush(mTargetColor);
        QRect tmpRect = rect().adjusted(i, i, -i, -i);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
        p.setBrush(lg);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
    }
}

void InnerWidget::DrawRightTop(QPainter &p)
{
    QPainterPath clipPath;
    QRect rightTop(rect().x() + rect().width() - mRadius, rect().y(), mRadius, mRadius);
    clipPath.addRect(rightTop);
    p.setClipPath(clipPath);
    QLinearGradient lg(rightTop.x(), rightTop.y(), rightTop.x() + rightTop.width(), rightTop.y() + rightTop.height());
    for (int i = 0; i < mShadowLength; ++i) {
        QColor startColor = mShadowDark;
        startColor.setAlpha(startColor.alpha() - (startColor.alpha() / mShadowLength) * i);
        QColor endColor = mShadowLight;
        int perRed = (mShadowLight.red() - mTargetColor.red()) / mShadowLength;
        endColor.setRed(endColor.red() - i * perRed);
        int perGreen = (mShadowLight.green() - mTargetColor.green()) / mShadowLength;
        endColor.setGreen(endColor.green() - i * perGreen);
        int perBlue = (mShadowLight.blue() - mTargetColor.blue()) / mShadowLength;
        endColor.setBlue(endColor.blue() - i * perBlue);
        lg.setColorAt(0, startColor);
        lg.setColorAt(1, endColor);
        p.setBrush(mTargetColor);
        QRect tmpRect = rect().adjusted(i, i, -i, -i);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
        p.setBrush(lg);
        p.drawRoundedRect(tmpRect, mRadius, mRadius);
    }
}
