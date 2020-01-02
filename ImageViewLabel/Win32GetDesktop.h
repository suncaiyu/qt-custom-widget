#ifndef FINDDESKTOP_H
#define FINDDESKTOP_H
#include <qt_windows.h>
#include <QWidget>
/*因为msvc编译器的缘故，要链接以下库文件*/
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "gdi32.lib")
/*分割*/
void iniworker();
void inisystem(QWidget *);
void ShowOnDesktop(QWidget *obj);
void QuitonDesktop();
#endif // FINDDESKTOP_H
