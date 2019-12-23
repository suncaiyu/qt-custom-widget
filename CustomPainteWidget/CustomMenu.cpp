#include "CustomMenu.h"
#include "ui_CustomMenu.h"

CustomMenu::CustomMenu(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::CustomMenu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::Popup);
}

CustomMenu::~CustomMenu()
{
    delete ui;
}

void CustomMenu::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}
