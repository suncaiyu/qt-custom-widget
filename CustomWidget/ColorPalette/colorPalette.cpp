#include "colorPalette.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include "math.h"

colorPalette::colorPalette(QWidget *parent) : QWidget(parent)
{

}

void colorPalette::mousePressEvent(QMouseEvent *event)
{
    pressPos = event->pos();

    if(isPointInCir(pressPos,boundingRect))
    {
        QString strDecimalValue,strHex;
        QPixmap pixmap(this->size());
        this->render(&pixmap);

        if (!pixmap.isNull())
        {
            QImage image = pixmap.toImage();
            if (!image.isNull())
            {
                int x = pressPos.x();
                int y = pressPos.y();

                QColor color = image.pixel(x, y);
                int red = color.red();
                int green = color.green();
                int blue = color.blue();

                strDecimalValue = QString("%1, %2, %3").arg(red).arg(green).arg(blue);
                strHex = QString("#%1%2%3").arg(QString("%1").arg(red&0xFF,2,16,QLatin1Char('0')).toUpper())    //red&0xFF 数字转成16进制
                                           .arg(QString("%1").arg(green&0xFF,2,16,QLatin1Char('0')).toUpper())
                                           .arg(QString("%1").arg(blue&0xFF,2,16,QLatin1Char('0')).toUpper());
            }
        }
        qDebug()<<strDecimalValue<<pressPos;
        emit colorString(strDecimalValue);
        update();
    }

    QWidget::mousePressEvent(event);
}

void colorPalette::resizeEvent(QResizeEvent *event)
{
    pressPos = QPoint();
    QWidget::resizeEvent(event);
}

void colorPalette::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);  //反走样开启
    const auto rect = event->rect();

    radius = std::min(rect.width(),rect.height()) / 2 - 5;
    boundingRect = QRect((rect.width() - 2*radius) / 2,(rect.height() - 2*radius) / 2,radius*2,radius*2);

    QConicalGradient conicalGradient(0, 0, 0); //创建渐变 前两个参数是渐变的中心点  第三个参数是渐变的角度

    QList<Qt::GlobalColor> list{Qt::red,
                                Qt::yellow,
                                Qt::green,
                                Qt::cyan,
                                Qt::blue,
                                Qt::magenta};

    for(int i = 0;i < list.size();++i)
    {
        conicalGradient.setColorAt(60.0 * i/360.0, list[i]);
    }
    conicalGradient.setColorAt(1.0, list[0]);

    painter.save();
    painter.translate(rect.center()); //将坐标系的原点设置为(r,r)
    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(0, 0), radius, radius);
    painter.restore();

    if(!pressPos.isNull())
    {
        painter.save();
        QPen pen;
        pen.setWidth(3);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawLine(QPoint(pressPos.x()-10,pressPos.y()),QPoint(pressPos.x()-7,pressPos.y()));
        painter.drawLine(QPoint(pressPos.x()+7,pressPos.y()),QPoint(pressPos.x()+10,pressPos.y()));

        painter.drawLine(QPoint(pressPos.x(),pressPos.y()-10),QPoint(pressPos.x(),pressPos.y()-7));
        painter.drawLine(QPoint(pressPos.x(),pressPos.y()+7),QPoint(pressPos.x(),pressPos.y()+10));

        painter.restore();
    }

    QWidget::paintEvent(event);
}

bool colorPalette::isPointInCir(const QPoint &point,const QRect & rect)
{
    const QPoint & centerPoint = rect.center();
    int x = point.x() - centerPoint.x();
    int y = point.y() - centerPoint.y();
    if(sqrt(pow(x,2) + pow(y,2)) <= (rect.width() / 2))
    {
        return true;
    }
    return false;
}
