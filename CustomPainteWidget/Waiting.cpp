#include "Waiting.h"
#include "ui_Waiting.h"
#include <QMovie>
#include <QDebug>
#include <QPainter>

wating::wating(QWidget *parent) : QWidget(parent), ui(new Ui::Waiting)
{
    ui->setupUi(this);
    this->setFixedSize(200, 200);
    background = new QFrame(this);
    background->setStyleSheet("background-color:#fff;border-radius:10px;");
    background->setGeometry(0, 50, 200, 150);
    label = new QLabel(background);
    label->setGeometry(0, 0, 200, 150);
    movie = new QMovie(":/image/loading.gif");
    movie->setScaledSize(QSize(200, 150));
    label->setScaledContents(true);
    label->setMovie(movie);
    movie->start();
    qDebug() << "loading";
    connect(this, SIGNAL(loading()), this, SLOT(close()));
    setAttribute(Qt::WA_TranslucentBackground);
}


wating::~wating()
{
    //一定要delete界面元素,不然会留下现一个透明方框
    delete background;
    delete label;
    delete movie;
    delete ui;
}

void wating::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.fillRect(rect(), QBrush(Qt::white));
}
