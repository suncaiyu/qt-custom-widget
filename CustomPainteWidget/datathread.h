#ifndef DATATHREAD_H
#define DATATHREAD_H

#include <qthread>
#include <qmutex>
class DataThread :public QThread
{
Q_OBJECT
public:
    DataThread();
    void run();//线程入口函数（工作线程的主函数）
    void appendPoint(float x,float y);
    QMutex mutex;
    bool stop;
    float x;
};

#endif // DATATHREAD_H
