#include "LeftPanel.h"
#include "ui_LeftPanel.h"
#include <QPainter>

LeftPanel::LeftPanel(QWidget *parent) :
      QFrame(parent),
      ui(new Ui::LeftPanel)
{
    ui->setupUi(this);
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
