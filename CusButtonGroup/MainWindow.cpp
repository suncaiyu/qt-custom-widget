#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CusButtonGroup.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CusButtonGroup *w4 = new CusButtonGroup;
    //设置下划线颜色
    w4->setButtonColor(QColor(255, 163, 69));
    //设置下划线高度
    w4->setLineHeight(4);
    //设置下划线高度
    w4->setButtonPosition(CusButtonGroup::South);
    for (int index = 0; index < 6; ++index) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(QString("Button_%1").arg(index));
        w4->addButton(btn, index, 32, QColor(255,255,233));
    }
    w4->setFixedHeight(36);
    w4->setDurnation(500);
    ui->verticalLayout->insertWidget(0,w4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

