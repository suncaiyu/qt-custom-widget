#include "datathread.h"
#include <QDebug>
QList<float> globalxList;
QList<float> globalyList;
DataThread::DataThread()
{
    stop = false;
    x =0;
}

void DataThread::appendPoint(float x,float y)
{
    mutex.lock();
    globalxList.append(x);
    globalyList.append(y);
    mutex.unlock();
}
void DataThread::run()
{
    while(!stop)
    {
        QString str="模拟数据:";
        int num;
        num = qrand()%100;
        str += QString::number(num);

        appendPoint(x,num);
        x=x+10;
//        qDebug() << str;
        QThread::msleep(1000);
    }
}
