#include "chartpanel.h"
#include "ui_chartpanel.h"
#include <QPainter>
#include <QDebug>
ChartPanel::ChartPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartPanel)
{
    ui->setupUi(this);
    count = 0;
}

ChartPanel::~ChartPanel()
{
    delete ui;
}
void ChartPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::darkCyan);
    pen.setStyle(Qt::SolidLine);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(pen);
    painter.fillRect(0,0, width(), height(), Qt::black);
    painter.drawLine(0,height()/2, width(),height()/2);
    painter.drawLine(0,height()/2-100, width(),height()/2-100);
    painter.drawText(0,20,QString("某设备压力图"));
    painter.drawText(0,height()/2,QString("0"));
    painter.drawText(0,height()/2-100,QString("100"));
    pen.setColor(Qt::green);
    painter.setPen(pen);
   for(int i = 0; i < xList.count(); i++)
    {
       if(i==0);
       else
       {
            painter.drawLine(xList[i-1]+width()-10*count,height()/2-yList[i-1], xList[i]+width()-10*count,height()/2-yList[i]);
            QString str;
            str.sprintf("%.0f",yList[i]);
            if(i == xList.count()-1)
            painter.drawText(xList[i]+width()-10*count-10,height()/2-yList[i],str);
       }
   }



}

void ChartPanel::chartAppendPoint(float x,float y)
{
    count++;
    if(xList.count()>1000)
    {
        xList.clear();
        yList.clear();
    }
    xList.append(x);
    yList.append(y);

    update();
}
