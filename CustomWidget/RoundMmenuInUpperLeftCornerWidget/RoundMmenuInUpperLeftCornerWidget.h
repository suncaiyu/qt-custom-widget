#ifndef ROUNDMMENUINUPPERLEFTCORNERWIDGET_H
#define ROUNDMMENUINUPPERLEFTCORNERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainterPath>

class RoundMmenuInUpperLeftCornerWidget : public QWidget
{
    Q_OBJECT

public:
    RoundMmenuInUpperLeftCornerWidget(QWidget *parent = nullptr);
    ~RoundMmenuInUpperLeftCornerWidget()override;

protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;

private:
    void onTimer();
    enum class State
    {
        Shrink,//收缩
        Popped,//已弹出
        Popping//正在弹出
    };
    State widgetState{State::Shrink};
    State lastWidgetState{State::Shrink};
    QRect homeBtnRect;
    QTimer timer;
    int Length{0};
    int radius{0};
    int outSideRadius{0};
    QList<QPixmap> imgList;
    QList<QRect> menuRectList;
    int pressIndexInMenuRectList{-1};
    QPoint pressPos{0,0};
    QPainterPath arcAreaPath;
    int allBeforeAngleOffset{0};
    int currentOffset{0};
};
#endif // ROUNDMMENUINUPPERLEFTCORNERWIDGET_H
