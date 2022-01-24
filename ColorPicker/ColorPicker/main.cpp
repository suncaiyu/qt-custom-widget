#include "Widget.h"

#include <QApplication>
#include <QSingleApplication.h>

int main(int argc, char *argv[])
{
    QSingleApplication a(argc, argv, "Furrain's Color Picker");
    if (a.IsRunning()) {
        a.SendMessage("notify");
        return 0;
    }
    Widget w;
    w.setWindowTitle("Color Picker");
//    QObject::connect(&a, &QSingleApplication::MessageAvailableSignal, &w, &Widget::RestartSlot);
    QObject::connect(&a, &QSingleApplication::MessageAvailableSignal, &w, [&w](){
        QMetaObject::invokeMethod(&w, "RestartSlot");
    });
    w.show();
    return a.exec();
}
