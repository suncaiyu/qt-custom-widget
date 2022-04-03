#include "FlipGraphicsView.h"
#include <QDebug>
FlipGraphicsView::FlipGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    QScopedPointer<QGraphicsScene> s(new QGraphicsScene);
    mScene.swap(s);
    setScene(mScene.get());
    QScopedPointer<QTimeLine> p(new QTimeLine(1200));
    mTimeline.swap(p);
    mTimeline->setStartFrame(0);
    mTimeline->setEndFrame(180);
}

FlipGraphicsView::~FlipGraphicsView()
{

}

void FlipGraphicsView::SetWidgets(QWidget *w1, QWidget *w2)
{
    pw1 = scene()->addWidget(w1);
    pw2 = scene()->addWidget(w2);
//    pw1->setWindowFlags(pw1->windowFlags() | Qt::Window);
//    pw2->setWindowFlags(pw1->windowFlags() | Qt::Window);
    pw2->setTransform(QTransform().translate(pw2->boundingRect().width() / 2, pw2->boundingRect().height() / 2)
                      .rotate(-180,Qt::YAxis)
                      .translate(-pw2->boundingRect().width() / 2,-pw2->boundingRect().height() / 2));
    pw2->setVisible(false);
    QObject::connect(mTimeline.get(), &QTimeLine::frameChanged,[this](const int frame){
        //对于登录窗体正常旋转
        pw1->setTransform(QTransform().translate(pw1->boundingRect().width()/2,pw1->boundingRect().height()/2)
                          .rotate(frame,Qt::YAxis)
                          .translate(-pw1->boundingRect().width()/2,-pw1->boundingRect().height()/2));
        //对于设置窗体由于开始旋转到了-180度，所以现在应该是-179,-176,-170....,0,这里应该是frame-180;也就是加上起点为-180度啦
        pw2->setTransform(QTransform().translate(pw2->boundingRect().width()/2,pw2->boundingRect().height()/2)
                          .rotate(frame - 180,Qt::YAxis)
                          .translate(-pw2->boundingRect().width()/2,-pw2->boundingRect().height()/2));

        switch (mTimeline->direction()) {
        case QTimeLine::Forward: //前面向后面转，frame从0到180，当frame大于或等于90度时，显示设置窗体，登录窗体隐藏
            if(frame > 90 || frame == 90){
                pw1->setVisible(false);
                pw2->setVisible(true);
            }
            break;
        case QTimeLine::Backward: //后面向前面转，frame从180到0，当frame小于或等于90度时，显示登录窗体，设置窗体隐藏
            if(frame < 90 || frame == 90){
                pw1->setVisible(true);
                pw2->setVisible(false);
            }
            break;
        }
    });
    //旋转结束后，设置线形闹钟值的方向
    QObject::connect(mTimeline.get(), &QTimeLine::finished, [this]{
        mTimeline->toggleDirection();
        qDebug() << "close";
    });
}

void FlipGraphicsView::StartFlipSlot()
{
    mTimeline->start();
}
