#ifndef CUSTOMSCROLLBAR_H
#define CUSTOMSCROLLBAR_H

#include <QWidget>
#include <QPropertyAnimation>
#include "FontAwesomeHelper.h"

class CustomScrollbar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal op READ GetOp WRITE SetOp)
public:
    explicit CustomScrollbar(Qt::Orientation a = Qt::Orientation::Horizontal, QWidget *parent = nullptr);
    virtual ~CustomScrollbar();
    void SetMaximum(qreal v) { mVirtualMaxValue = v; };
    void SetPageStep(qreal v) { mPageStep = v; };
    void SetValue(qreal v);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void ValueChangeSignal(qreal value);
    void MouseEnterSignal();
    void MouseLeaveSignal();

private:
    // 总value
    qreal mVirtualMaxValue = 10000;
    // 当前比例值 0.0 - 1.0
    qreal mValue = 0.0;
    // pagestep;
    qreal mPageStep = 10;
    // 除去控制器的宽度
    qreal mScrollWidth = 0.0;
    qreal mPerPixelToValue;
    QRectF mPageStepRect = QRectF(0, 0, 0, 0);
    bool mIsPressed = false;
    qreal mPressDistance;
    qreal op = 0.0;
    QSharedPointer<QPropertyAnimation> mAnimation;
    Qt::Orientation mOrientation = Qt::Orientation::Horizontal;

    qreal GetOp() { return op; };
    void SetOp(qreal v) { op = v; update(); };
    void DrawControl(QPainter &p);
};

#endif // CUSTOMSCROLLBAR_H
