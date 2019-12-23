#include "widgetsizeandmove.h"
#include "qevent.h"
#include "qdebug.h"

ReSizeAndMoveWidget::ReSizeAndMoveWidget(QObject *parent) : QObject(parent)
{
    padding = 8;
    titleBarHeight = 100;

    widget = 0;

    pressed = false;
    pressedLeft = false;
    pressedRight = false;
    pressedTop = false;
    pressedBottom = false;
    pressedLeftTop = false;
    pressedRightTop = false;
    pressedLeftBottom = false;
    pressedRightBottom = false;


}

bool ReSizeAndMoveWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (widget != 0 && watched == widget) {
        if (event->type() == QEvent::Resize) {
            //重新计算八个描点的区域,描点区域的作用还有就是计算鼠标光标是否在某一个区域内
            int width = widget->width();
            int height = widget->height();

            //左侧描点区域
            rectLeft = QRect(0, padding, padding, height - padding * 2);
            //上侧描点区域
            rectTop = QRect(padding, 0, width - padding * 2, padding);
            //右侧描点区域
            rectRight = QRect(width - padding, padding, padding, height - padding * 2);
            //下侧描点区域
            rectBottom = QRect(padding, height - padding, width - padding * 2, padding);

            //左上角描点区域
            rectLeftTop = QRect(0, 0, padding, padding);
            //右上角描点区域
            rectRightTop = QRect(width - padding, 0, padding, padding);
            //左下角描点区域
            rectLeftBottom = QRect(0, height - padding, padding, padding);
            //右下角描点区域
            rectRightBottom = QRect(width - padding, height - padding, padding, padding);
        } else if (event->type() == QEvent::HoverMove) {
            QHoverEvent *hoverEvent = (QHoverEvent *)event;
            QPoint point = hoverEvent->pos();

            if (rectLeft.contains(point)) {
                widget->setCursor(Qt::SizeHorCursor);
            } else if (rectRight.contains(point)) {
                widget->setCursor(Qt::SizeHorCursor);
            } else if (rectTop.contains(point)) {
                widget->setCursor(Qt::SizeVerCursor);
            } else if (rectBottom.contains(point)) {
                widget->setCursor(Qt::SizeVerCursor);
            } else if (rectLeftTop.contains(point)) {
                widget->setCursor(Qt::SizeFDiagCursor);
            } else if (rectRightTop.contains(point)) {
                widget->setCursor(Qt::SizeBDiagCursor);
            } else if (rectLeftBottom.contains(point)) {
                widget->setCursor(Qt::SizeBDiagCursor);
            } else if (rectRightBottom.contains(point)) {
                widget->setCursor(Qt::SizeFDiagCursor);
            } else {
                widget->setCursor(Qt::ArrowCursor);
            }


            //根据当前鼠标位置,计算XY轴移动了多少
            int offsetX = point.x() - lastPos.x();
            int offsetY = point.y() - lastPos.y();

            //根据按下处的位置判断是否是移动控件还是拉伸控件

            if (pressed) {
                widget->move(widget->x() + offsetX, widget->y() + offsetY);
            }

            if (pressedLeft) {
                int resizeW = widget->width() - offsetX;
                if (widget->minimumWidth() <= resizeW) {
                    widget->setGeometry(widget->x() + offsetX, rectY, resizeW, rectH);
                }
            } else if (pressedRight) {
                widget->setGeometry(rectX, rectY, rectW + offsetX, rectH);
            } else if (pressedTop) {
                int resizeH = widget->height() - offsetY;
                if (widget->minimumHeight() <= resizeH) {
                    widget->setGeometry(rectX, widget->y() + offsetY, rectW, resizeH);
                }
            } else if (pressedBottom) {
                widget->setGeometry(rectX, rectY, rectW, rectH + offsetY);
            } else if (pressedLeftTop) {
                int resizeW = widget->width() - offsetX;
                int resizeH = widget->height() - offsetY;
                if (widget->minimumWidth() <= resizeW) {
                    widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                }
                if (widget->minimumHeight() <= resizeH) {
                    widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                }
            } else if (pressedRightTop) {
                int resizeW = rectW + offsetX;
                int resizeH = widget->height() - offsetY;
                if (widget->minimumHeight() <= resizeH) {
                    widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                }
            } else if (pressedLeftBottom) {
                int resizeW = widget->width() - offsetX;
                int resizeH = rectH + offsetY;
                if (widget->minimumWidth() <= resizeW) {
                    widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                }
                if (widget->minimumHeight() <= resizeH) {
                    widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
                }
            } else if (pressedRightBottom) {
                int resizeW = rectW + offsetX;
                int resizeH = rectH + offsetY;
                widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
            }

        } else if (event->type() == QEvent::MouseButtonPress) {
            //记住当前控件坐标和宽高以及鼠标按下的坐标
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            rectX = widget->x();
            rectY = widget->y();
            rectW = widget->width();
            rectH = widget->height();
            lastPos = mouseEvent->pos();

            //判断按下的手柄的区域位置
            if (rectLeft.contains(lastPos)) {
                pressedLeft = true;
            } else if (rectRight.contains(lastPos)) {
                pressedRight = true;
            } else if (rectTop.contains(lastPos)) {
                pressedTop = true;
            } else if (rectBottom.contains(lastPos)) {
                pressedBottom = true;
            } else if (rectLeftTop.contains(lastPos)) {
                pressedLeftTop = true;
            } else if (rectRightTop.contains(lastPos)) {
                pressedRightTop = true;
            } else if (rectLeftBottom.contains(lastPos)) {
                pressedLeftBottom = true;
            } else if (rectRightBottom.contains(lastPos)) {
                pressedRightBottom = true;
            } else {
                if(lastPos.y()<=titleBarHeight){
                    pressed = true;
                }
            }
        } else if (event->type() == QEvent::MouseMove) {
          ;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            //恢复所有
            pressed = false;
            pressedLeft = false;
            pressedRight = false;
            pressedTop = false;
            pressedBottom = false;
            pressedLeftTop = false;
            pressedRightTop = false;
            pressedLeftBottom = false;
            pressedRightBottom = false;
            widget->setCursor(Qt::ArrowCursor);
        }
    }

    return QObject::eventFilter(watched, event);
}

void ReSizeAndMoveWidget::setWidget(QWidget *widget)
{
    if (this->widget == 0) {
        this->widget = widget;
        this->widget->setMouseTracking(true);
        this->widget->installEventFilter(widget);        
        this->widget->setAttribute(Qt::WA_Hover, true);        
    }
}
