#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgetsizeandmove.h"
#include "CustomMenu.h"
#include "LeftPanel.h"
#include "chartpanel.h"
#include "datathread.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *obj,QEvent *e);
    void resizeEvent(QResizeEvent *e);

private slots:
    void on_menu_menu_clicked();

    void on_menu_Minimize_clicked();

    void on_menu_Maxmize_clicked();

    void on_menu_close_clicked();

    void Update();

private:
    Ui::MainWindow *ui;
    ReSizeAndMoveWidget *pReSizeAndMoveWidget;
    bool max = false;
    CustomMenu *pCustomMenu;
    LeftPanel *leftpanel;
    ChartPanel *chartPanel;
    DataThread *thread;
    QTimer *time;
};
#endif // MAINWINDOW_H
