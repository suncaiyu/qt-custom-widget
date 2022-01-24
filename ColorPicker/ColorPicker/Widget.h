#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHotkey>
#include <QSystemTrayIcon>
#include <DebugColorDialog.h>
#include "utils.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void SetSystemIcon();
    QPixmap GetPixmap();
    void DrawPixmap(QPainter &p);
    void DrawMark(QPainter &p, int distanceX, int distanceY);
    void DrawPosition(QPainter &p);
    void DrawScale(QPainter &p);
    void DrawRGB(QPainter &p);
    void DrawHex(QPainter &p);
    void DrawTip(QPainter &p);
    void DrawHelp(QPainter &p);
    int GetSuitableWidth(QPainter &p, QString str);

    Ui::Widget *ui;
    int mTimeId = -1;
    int mScale = 8;
    QPoint mPos;
    ColorString mCs;
    bool mShowText = true;
    bool mShowHelp = false;
    QSharedPointer<QHotkey> mHotkey;
    QSharedPointer<QAction> mExit;
    QSharedPointer<QMenu> mMenu;
    QSharedPointer<QSystemTrayIcon> mSystemIcon;
    QSharedPointer<DebugColorDialog> mDebugDialog;

public slots:
    void RestartSlot();
};
#endif // WIDGET_H
