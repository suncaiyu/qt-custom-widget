#ifndef LAMBDATHREAD_H
#define LAMBDATHREAD_H
#include <QObject>
#include <QThread>
#include <QSemaphore>

class LambdaThread : public QObject
{
private:
    Q_OBJECT

    std::function<void()> m_func;
    QThread *m_Thread;
    QSemaphore completed;
    bool m_SelfDelete = false;
    QString m_Name;

    void windowsSetName() {}

public slots:
    void process()
    {
//        if(!m_Name.isEmpty()) {
//            windowsSetName();
//        }
        m_func();
        m_Thread->quit();
        if(m_SelfDelete) {
            deleteLater();
        }
        completed.acquire();
    }

    void selfDelete(bool d) { m_SelfDelete = d; }
signals:
    void ThreadFinished();
public:
    explicit LambdaThread(std::function<void()> f)
    {
        completed.release();
        m_Thread = new QThread();
        m_func = f;
        moveToThread(m_Thread);
        QObject::connect(m_Thread, &QThread::started, this, &LambdaThread::process);
        connect(m_Thread, &QThread::finished, [this](){
            ThreadFinished();
            m_Thread->deleteLater();
        });
    }

    ~LambdaThread() { m_Thread->deleteLater(); }
    void setName(QString name) {
        m_Name = name;
        m_Thread->setObjectName(name);
    }
    void start(QThread::Priority prio = QThread::InheritPriority) { m_Thread->start(prio); }
    bool isRunning() { return completed.available(); }
    bool wait(unsigned long time = ULONG_MAX) {
        if(m_Thread) {
            return m_Thread->wait(time);
        }
        return true;
    }

    void moveObjectToThread(QObject *o) { o->moveToThread(m_Thread); }
    bool isCurrentThread() { return QThread::currentThread() == m_Thread; }
};
#endif // LAMBDATHREAD_H
