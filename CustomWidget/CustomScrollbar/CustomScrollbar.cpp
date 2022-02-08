#include "CustomScrollbar.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QFontDatabase>
#include <QAbstractSlider>
namespace {
constexpr qreal CONTROL_SIZE = 20;
constexpr qreal MIN_PAGE_WIDTH = 20;
}
CustomScrollbar::CustomScrollbar(Qt::Orientation a, QWidget* parent) : QWidget(parent)
{
    mOrientation = a;
    if (mOrientation == Qt::Orientation::Horizontal) {
        setFixedHeight(CONTROL_SIZE);
    }
    else {
        setFixedWidth(CONTROL_SIZE);
    }
    mAnimation = QSharedPointer<QPropertyAnimation>(new QPropertyAnimation(this, "op", this));
    mAnimation->setEasingCurve(QEasingCurve::OutQuart);
}

CustomScrollbar::~CustomScrollbar()
{

}

void CustomScrollbar::SetValue(qreal v)
{
    mValue = v / mVirtualMaxValue;
    mValue = qBound(0.0, mValue, (mVirtualMaxValue - mPageStep) / mVirtualMaxValue);
    update();
}

void CustomScrollbar::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    if (mOrientation == Qt::Orientation::Horizontal) {
        mScrollWidth = width() - 2.0 * CONTROL_SIZE;
        mPerPixelToValue = mVirtualMaxValue / mScrollWidth;
        qreal pageWidth = mPageStep / mPerPixelToValue;
        qreal pageStart = mVirtualMaxValue * mValue / mPerPixelToValue + CONTROL_SIZE;
        if (pageWidth < MIN_PAGE_WIDTH) {
            pageWidth = MIN_PAGE_WIDTH;
            mScrollWidth = mScrollWidth - MIN_PAGE_WIDTH + mPageStep / mPerPixelToValue;
            mPerPixelToValue = mVirtualMaxValue / mScrollWidth;
            pageStart = (mVirtualMaxValue * mValue) / mPerPixelToValue + CONTROL_SIZE;
        }
        mPageStepRect.setRect(pageStart, 0, pageWidth, CONTROL_SIZE);
    } else {
        mScrollWidth = height() - 2.0 * CONTROL_SIZE;
        mPerPixelToValue = mVirtualMaxValue / mScrollWidth;
        qreal pageWidth = mPageStep / mPerPixelToValue;
        qreal pageStart = mVirtualMaxValue * mValue / mPerPixelToValue + CONTROL_SIZE;
        if (pageWidth < MIN_PAGE_WIDTH) {
            pageWidth = MIN_PAGE_WIDTH;
            mScrollWidth = mScrollWidth - MIN_PAGE_WIDTH + mPageStep / mPerPixelToValue;
            mPerPixelToValue = mVirtualMaxValue / mScrollWidth;
            pageStart = (mVirtualMaxValue * mValue) / mPerPixelToValue + CONTROL_SIZE;
        }
        mPageStepRect.setRect(0, pageStart, CONTROL_SIZE, pageWidth);
    }
    p.fillRect(rect(), Qt::white);
    p.fillRect(mPageStepRect, Qt::gray);
    DrawControl(p);
}

void CustomScrollbar::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
}

void CustomScrollbar::mousePressEvent(QMouseEvent* event)
{
    if (mPageStepRect.contains(event->pos())) {
        mIsPressed = true;
        if (mOrientation == Qt::Orientation::Horizontal) {
            mPressDistance = event->x() - mPageStepRect.x();
        } else {
            mPressDistance = event->y() - mPageStepRect.y();
        }
    }
}

void CustomScrollbar::mouseMoveEvent(QMouseEvent* event)
{
    if (!mIsPressed) {
        return;
    }
    qreal prevValue = mValue;
    QPointF current = event->pos();
    if (mOrientation == Qt::Orientation::Horizontal) {
        mValue = (current.x() - CONTROL_SIZE - mPressDistance) / mScrollWidth;
        mValue = qBound(0.0, mValue, (mVirtualMaxValue - mPageStep) / mVirtualMaxValue);
    }
    else {
        mValue = (current.y() - CONTROL_SIZE - mPressDistance) / mScrollWidth;
        mValue = qBound(0.0, mValue, (mVirtualMaxValue - mPageStep) / mVirtualMaxValue);
    }
    if (prevValue != mValue) {
        ValueChangeSignal(mVirtualMaxValue * mValue);
    }
    update();
}

void CustomScrollbar::mouseReleaseEvent(QMouseEvent* event)
{
    mIsPressed = false;
}

void CustomScrollbar::enterEvent(QEvent* event)
{
    QWidget::enterEvent(event);
    MouseEnterSignal();
    mAnimation->stop();
    mAnimation->setStartValue(op);
    mAnimation->setEndValue(1.0);
    mAnimation->setDuration(1000);
    mAnimation->start();
}

void CustomScrollbar::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    MouseLeaveSignal();
    mAnimation->stop();
    mAnimation->setStartValue(op);
    mAnimation->setEndValue(0.0);
    mAnimation->setDuration(1000);
    mAnimation->start();
}

void CustomScrollbar::DrawControl(QPainter &p)
{
    FontAwesomeHelper *helper = FontAwesomeHelper::GetInstance();
    p.setFont(helper->GetAwesomeFont());
    if (mOrientation == Qt::Orientation::Horizontal) {
        QRectF left, right;
        left = QRectF(0, 0, CONTROL_SIZE, CONTROL_SIZE);
        right = QRectF(width() - CONTROL_SIZE, 0, CONTROL_SIZE, CONTROL_SIZE);
        p.setOpacity(op);
        p.drawText(left, Qt::AlignCenter, helper->IconUnicode("chevron-left"));
        p.drawText(right, Qt::AlignCenter, helper->IconUnicode("chevron-right"));
    } else {
        QRectF left, right;
        left = QRectF(0, 0, CONTROL_SIZE, CONTROL_SIZE);
        right = QRectF(0, height() - CONTROL_SIZE, CONTROL_SIZE, CONTROL_SIZE);
        p.setOpacity(op);
        p.drawText(left, Qt::AlignCenter, helper->IconUnicode("chevron-up"));
        p.drawText(right, Qt::AlignCenter, helper->IconUnicode("chevron-down"));
    }
}
