#include "pushbutton.h"
PushButton::PushButton(QWidget *parent)
    :QPushButton(parent)
{
    status = NORMAL;
    mouse_press = false;
}
PushButton::~PushButton()
{
}
void PushButton::setButtomImagePath(QString Icon_path)
{
    this->icon_path = Icon_path;
    QSize qsz =QPixmap(Icon_path).size();
    qsz.setWidth(qsz.width()/3);
    setFixedSize(qsz);//设置按钮与图片一样的大小
}

void PushButton::enterEvent(QEvent *)
{
    status = HOVER;
    update();
}
void PushButton::mousePressEvent(QMouseEvent *event)
{
    //若点击鼠标左键
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        status = PRESS;
        update();
    }
}
void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
    //若点击鼠标左键响应
    if(mouse_press&&this->rect().contains(event->pos()))
    {
        mouse_press = false;
        status = HOVER;
        update();
        emit clicked();
    }
}
void PushButton::leaveEvent(QEvent *)
{
    status = NORMAL;
    update();
}
void PushButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap;
    QRect rt;

    switch(status)
    {
    case NORMAL:
        {
            bool ret = pixmap.load(icon_path);
            rt = QRect(0,0,pixmap.size().width()/3,pixmap.size().height());
            break;
        }
    case HOVER:
        {
            pixmap.load(icon_path );
            rt = QRect(pixmap.size().width()/3,0,pixmap.size().width()/3,pixmap.size().height());
            break;
        }
    case PRESS:
        {
            pixmap.load(icon_path );
            rt = QRect((pixmap.size().width()*2)/3,0,pixmap.size().width()/3,pixmap.size().height());
            break;
        }
    default:
        pixmap.load(icon_path);
        rt = QRect(0,0,pixmap.size().width()/3,pixmap.size().height());
    }
    //rt = QRect(0,0,pixmap.size().width()/3,pixmap.size().height());
    painter.drawPixmap(rect(), pixmap,rt);
    painter.drawText(this->rect(), Qt::AlignCenter, this->text());
}
