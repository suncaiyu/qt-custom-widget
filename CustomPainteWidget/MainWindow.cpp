#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPainter>
#include <QStringLiteral>
extern QList<float> globalxList;
extern QList<float> globalyList;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    pReSizeAndMoveWidget = new ReSizeAndMoveWidget(this);
    pReSizeAndMoveWidget->setWidget(this);
    ui->menu_menu->setButtomImagePath(":/image/btn_menu.png");
    ui->menu_Minimize->setButtomImagePath(":/image/btn_minimize.png");
    ui->menu_Minimize->setToolTip(QStringLiteral("最小化"));
    ui->menu_menu->setToolTip(QStringLiteral("菜单"));
    ui->menu_Maxmize->setToolTip(QStringLiteral("最大化"));
    ui->menu_close->setToolTip(QStringLiteral("关闭"));
    ui->menu_close->setButtomImagePath(":/image/btn_close.png");
    ui->menu_Maxmize->setButtomImagePath(":/image/btn_maxmize.png");
    pCustomMenu = new CustomMenu;
    leftpanel = new LeftPanel(this);
    leftpanel->move(0, 100);
    leftpanel->show();
    chartPanel = new ChartPanel(this);
    chartPanel->show();
    thread = new DataThread();
    thread->start();


    time = new QTimer();
    connect(time,SIGNAL(timeout()),this,SLOT(Update()));
    time->start(50);
}


void MainWindow::Update()
{
    if (globalxList.size() > 0 && globalyList.size() > 0) {
        chartPanel->chartAppendPoint(globalxList[0], globalyList[0]);
        globalxList.removeFirst();
        globalyList.removeFirst();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    return pReSizeAndMoveWidget->eventFilter(obj, e);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QRect rect = this->rect();
    rect.adjust(0, 0, -1, -1);
    QPainter paint(this);
    paint.drawRect(rect);
    paint.fillRect(rect, QBrush(Qt::black));
    paint.fillRect(0, 0, rect.width(), 100, QBrush(QColor(47, 48, 53)));
    QPixmap pixmap;
    pixmap.load(":/image/logo.png");
    paint.drawPixmap(0, 0, 361, 100, pixmap);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    ui->menu_close->move(width() - 34, 4);
    ui->menu_Maxmize->move(width() - 34 - 34, 4);
    ui->menu_Minimize->move(width() - 34 - 34 - 34, 4);
    ui->menu_menu->move(width() - 34 - 34 - 34 - 34, 4);
    leftpanel->resize(leftpanel->width(), height() - 99);
    chartPanel->move(leftpanel->width(), 100);
    chartPanel->resize(width() - leftpanel->width(), height() - 99);
}


void MainWindow::on_menu_menu_clicked()
{
    pCustomMenu->move(QPoint(QCursor::pos()));
    pCustomMenu->show();
}

void MainWindow::on_menu_Minimize_clicked()
{
    showMinimized();
}

void MainWindow::on_menu_Maxmize_clicked()
{
    if (max) {
        showNormal();
        ui->menu_Maxmize->setButtomImagePath(":/image/btn_maxmize.png");

    } else {
        showMaximized();
        ui->menu_Maxmize->setButtomImagePath(":/image/btn_maxmize_normal.png");
    }
    max = !max;
}

void MainWindow::on_menu_close_clicked()
{
    qApp->exit();
}
