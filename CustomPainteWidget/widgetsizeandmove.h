#ifndef ReSizeAndMoveWidget_H
#define ReSizeAndMoveWidget_H


#include <QWidget>


class ReSizeAndMoveWidget : public QObject
{
    Q_OBJECT
public:
    explicit ReSizeAndMoveWidget(QObject *parent = 0);

public:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    int padding;                    //边距
    int titleBarHeight;             //标题栏高度
    QWidget *widget;                //无边框窗体

    bool pressed;                   //鼠标按下
    bool pressedLeft;               //鼠标按下左侧
    bool pressedRight;              //鼠标按下右侧
    bool pressedTop;                //鼠标按下上侧
    bool pressedBottom;             //鼠标按下下侧
    bool pressedLeftTop;            //鼠标按下左上侧
    bool pressedRightTop;           //鼠标按下右上侧
    bool pressedLeftBottom;         //鼠标按下左下侧
    bool pressedRightBottom;        //鼠标按下右下侧

    int rectX, rectY, rectW, rectH; //窗体坐标+宽高
    QPoint lastPos;                 //鼠标按下处坐标

    QRect rectLeft;                 //左侧区域
    QRect rectRight;                //右侧区域
    QRect rectTop;                  //上侧区域
    QRect rectBottom;               //下侧区域
    QRect rectLeftTop;              //左上侧区域
    QRect rectRightTop;             //右上侧区域
    QRect rectLeftBottom;           //左下侧区域
    QRect rectRightBottom;          //右下侧区域
public:
    //设置要无边框的窗体
    void setWidget(QWidget *widget);
public Q_SLOTS:

};

#endif // ReSizeAndMoveWidget_H
