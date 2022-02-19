#ifndef GUIINVOKE_H
#define GUIINVOKE_H
#include <functional>
#include <QPointer>

class GUIInvoke : public QObject
{
private:
  Q_OBJECT
  GUIInvoke(QObject *obj, const std::function<void()> &f) : ptr(obj), func(f) {}
  QPointer<QObject> ptr;
  std::function<void()> func;

  static int methodIndex;

public:
  static void init();
  static void call(QObject *obj, const std::function<void()> &f);
  static void blockcall(QObject *obj, const std::function<void()> &f);
  static bool onUIThread();

  // same as call() above, but it doesn't check for an instant call on the UI thread
  static void defer(QObject *obj, const std::function<void()> &f);

protected slots:
  void doInvoke()
  {
    if(ptr)
      func();
    deleteLater();
  }
};

#endif // GUIINVOKE_H
