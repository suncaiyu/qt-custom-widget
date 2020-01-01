#include "pushcombox.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopWidget>
#include <QListView>
pushcombox::pushcombox(QWidget *widget) : QPushButton(widget)
{
    m_currindex=0;
    m_currenttext="---";
    listPanel=new QWidget(widget);
    listview=new QListView;
    listview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(listview);
    layout->setContentsMargins(0,0,0,0);
    listPanel->setLayout(layout);
    model=new QStringListModel;
    listview->setModel(model);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listPanel->hide();
    connect(listview,SIGNAL(clicked(QModelIndex)),SLOT(on_clicked()));
    connect(this,SIGNAL(clicked(bool)),this,SLOT(on_showPopup()));
}
void pushcombox::addtextItem(QString str)
{
    QStringList list;
    list=model->stringList();
    list+=str;
    model->setStringList(list);
    this->setText(list.at(m_currindex));
}
void pushcombox::on_clicked()
{
    qDebug()<<"on_clicked";
    QStringList list;
    list=model->stringList();
    this->setText(list.at(listview->currentIndex().row()));
    setCurrentIndex(listview->currentIndex().row());
    setCurrentText(list.at(listview->currentIndex().row()));
    listPanel->hide();
}
void pushcombox::on_showPopup()
{
    qDebug()<<"on_showPopup";
    if(!listPanel->isHidden())
    {
        listPanel->hide();
        return;
    }

    int height=20*listview->model()->rowCount();
    //if(height>window()->height()-this->y())
        //height=this->y();
    listPanel->resize(this->width(),height);
    listPanel->move(this->x(),this->y() + this->height());
    listPanel->show();
}
void pushcombox::addtextItems(QStringList list)
{
    model->setStringList(list);
    this->setText(list.at(m_currindex));
}
void pushcombox::setCurrentIndex(int i)
{
    if(i==m_currindex)
        return;
    m_currindex=i;
    QStringList list;
    list=model->stringList();
    this->setText(list.at(m_currindex));
    emit currentIndexChanged(m_currindex);
}
void pushcombox::setCurrentText(QString str)
{
    if(str==m_currenttext)
        return;
    m_currenttext=str;
    emit currentTextChanged(m_currenttext);
}

