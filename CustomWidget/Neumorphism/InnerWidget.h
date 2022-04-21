#ifndef INNERWIDGET_H
#define INNERWIDGET_H

#include <QWidget>

class InnerWidget : public QWidget
{
    Q_OBJECT
public:
    InnerWidget(QWidget *parent = 0);
    ~InnerWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void DrawLeftTop(QPainter &p);
    void DrawRightBottom(QPainter &p);
    void DrawLeftBottom(QPainter &p);
    void DrawRightTop(QPainter &p);
    QColor mTargetColor;
    QColor mShadowDark;
    QColor mShadowLight;
    int mShadowLength = 5;
    int mRadius = 20;
};

#endif // INNERWIDGET_H
