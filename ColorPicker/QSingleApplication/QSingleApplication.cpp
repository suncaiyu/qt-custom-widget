#include "QSingleApplication.h"
#include <QLocalSocket>

QSingleApplication::QSingleApplication(int &argc, char *argv[], const QString uniqueKey)
    : QApplication(argc, argv), mUniqueKey(uniqueKey)
{
    mSharedMemory.setKey(mUniqueKey);
    if (mSharedMemory.attach()) {
        mIsRunning = true;
    } else {
        mIsRunning = false;
        // create shared memory.
        if (!mSharedMemory.create(1)) {
            qDebug("Unable to create single instance.");
            return;
        }

        // create local server and listen to incomming messages from other instances.
        // 准备接受消息
        mLocalServer = QSharedPointer<QLocalServer>(new QLocalServer(this));
        connect(mLocalServer.get(), SIGNAL(newConnection()), this, SLOT(ReceiveMessageSlot()));
        mLocalServer->listen(mUniqueKey);
    }
}

QSingleApplication::~QSingleApplication()
{
}

bool QSingleApplication::IsRunning()
{
    return mIsRunning;
}
// 发送信息，告诉之前启动的程序
bool QSingleApplication::SendMessage(const QString message)
{
    if (!mIsRunning) {
        return false;
    }
    QLocalSocket localSocket(this);
    localSocket.connectToServer(mUniqueKey, QIODevice::WriteOnly);
    if (!localSocket.waitForConnected(mTimeout)) {
        qDebug() << localSocket.errorString().toLatin1();
        return false;
    }

    localSocket.write(message.toUtf8());
    if (!localSocket.waitForBytesWritten(mTimeout)) {
        qDebug() << localSocket.errorString().toLatin1();
        return false;
    }

    localSocket.disconnectFromServer();
    return true;
}

// 收到第二次启动的程序发送的信息
void QSingleApplication::ReceiveMessageSlot()
{
    QLocalSocket *localSocket = mLocalServer->nextPendingConnection();
    if (!localSocket->waitForReadyRead(mTimeout)) {
        qDebug() << localSocket->errorString().toLatin1();
        return;
    }

    QByteArray byteArray = localSocket->readAll();
    QString message = QString::fromUtf8(byteArray.constData());
    emit MessageAvailableSignal(message);
    localSocket->disconnectFromServer();
}

