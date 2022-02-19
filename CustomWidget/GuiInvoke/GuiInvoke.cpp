#include "GuiInvoke.h"
#include <QDebug>
#include <QApplication>
#include <QMetaMethod>
#include <QThread>

int GUIInvoke::methodIndex = -1;
void GUIInvoke::init()
{
    GUIInvoke *invoke = new GUIInvoke(NULL, {});
    methodIndex = invoke->metaObject()->indexOfMethod(QMetaObject::normalizedSignature("doInvoke()"));
    invoke->deleteLater();
}

void GUIInvoke::call(QObject *obj, const std::function<void()> &f)
{
    if(!obj) {
        qCritical() << "GUIInvoke::call called with NULL object";
    }
    if(onUIThread()) {
        if(obj) {
            f();
        }
        return;
    }
    defer(obj, f);
}

void GUIInvoke::defer(QObject *obj, const std::function<void()> &f)
{
    if(!obj)
        qCritical() << "GUIInvoke::defer called with NULL object";

    GUIInvoke *invoke = new GUIInvoke(obj, f);
    invoke->moveToThread(qApp->thread());
    bool flag = invoke->metaObject()->method(methodIndex).invoke(invoke, Qt::QueuedConnection);
    if (!flag) {
        init();
        invoke->metaObject()->method(methodIndex).invoke(invoke, Qt::QueuedConnection);
    }
}

void GUIInvoke::blockcall(QObject *obj, const std::function<void()> &f)
{
    if(!obj) {
        qCritical() << "GUIInvoke::blockcall called with NULL object";
    }
    if(onUIThread()) {
        if(obj) {
            f();
        }
        return;
    }

    GUIInvoke *invoke = new GUIInvoke(obj, f);
    invoke->moveToThread(qApp->thread());
    bool flag = invoke->metaObject()->method(methodIndex).invoke(invoke, Qt::BlockingQueuedConnection);
    if (!flag) {
        init();
        invoke->metaObject()->method(methodIndex).invoke(invoke, Qt::BlockingQueuedConnection);
    }
}

bool GUIInvoke::onUIThread()
{
    return qApp->thread() == QThread::currentThread();
}
