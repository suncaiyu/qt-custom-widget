#ifndef QSINGLEAPPLICATION_H
#define QSINGLEAPPLICATION_H

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

class QSingleApplication : public QApplication
{
    Q_OBJECT

public:
    QSingleApplication(int &argc, char *argv[], const QString uniqueKey);
    virtual ~QSingleApplication();
    bool IsRunning();
    bool SendMessage(const QString msg);

public slots:
    void ReceiveMessageSlot();

signals:
    void MessageAvailableSignal(QString msg);

private:
    bool mIsRunning;
    QString mUniqueKey;
    QSharedMemory mSharedMemory;
    QSharedPointer<QLocalServer> mLocalServer;
    const int mTimeout = 1000;
};
#endif // QSINGLEAPPLICATION_H
