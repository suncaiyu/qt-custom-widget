#include "mainwindow.h"
#include "pushcombox.h"
#include <QListView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pushcombox *com=new pushcombox(this);
    com->move(30,30);
    QStringListModel *model=new QStringListModel;
    QStringList list;
    list<<"1"<<"2"<<"3"<<"4";
    model->setStringList(list);
    com->addtextItems(list);
    com->addtextItem("5");
    com->addtextItem("6");
    //connect(com,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mycombobx(int)));
    //connect(com,SIGNAL(currentTextChanged(QString)),this,SLOT(on_mycombobx(QString)));
    resize(200,200);
}

MainWindow::~MainWindow()
{

}
