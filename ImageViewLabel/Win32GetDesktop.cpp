#include "Win32GetDesktop.h"

HWND hworkerw;
HWND workerw;

void iniworker() //获取proman窗口
{
    SendMessageTimeout(FindWindow(L"Progman", NULL), 0x52c, 0, 0, SMTO_NORMAL, 1000, NULL);
    hworkerw = NULL;
    HWND hdefview = NULL;
    hworkerw = FindWindowEx(NULL, NULL, L"WorkerW", NULL);
    while ((!hdefview) && hworkerw) {
        hdefview = FindWindowEx(hworkerw, NULL, L"SHELLDLL_DefView", NULL);
        workerw = hworkerw;
        hworkerw = FindWindowEx(NULL, hworkerw, L"WorkerW", NULL);
    }
    workerw = FindWindow(L"Progman", NULL);
}

void inisystem(QWidget *obj) //初始化窗口
{
    if (workerw) {
        SetParent((HWND) obj->winId(), hworkerw);
    }
}

void ShowOnDesktop(QWidget *obj)
{
    ShowWindow(hworkerw, 3);
    obj->showFullScreen();
}

void QuitonDesktop()
{
    ShowWindow(hworkerw, 0);
}
