#include "LeftPanel.h"
#include "ui_LeftPanel.h"
#include <QPainter>
#include "Waiting.h"
#include <Loading.h>
#include "myAnimationButton.h"

LeftPanel::LeftPanel(QWidget *parent) :
      QFrame(parent),
      ui(new Ui::LeftPanel)
{
    ui->setupUi(this);
    myAnimationButton *a = new myAnimationButton(this);
    ui->verticalLayout->addWidget(a);
    a->setImagePath(":/image/wechat.png");
}

LeftPanel::~LeftPanel()
{
    delete ui;
}

void LeftPanel::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.fillRect(rect(), QBrush(Qt::white));
}

void LeftPanel::on_commandLinkButton_clicked()
{
    Loading *l = new Loading;
    l->start();
    l->show();
}
