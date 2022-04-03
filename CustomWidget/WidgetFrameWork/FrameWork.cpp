#include "FrameWork.h"

FrameWork::FrameWork(QWidget *parent) : QWidget(nullptr), mParent(parent)
{
    ami1 = QSharedPointer<QPropertyAnimation>(new QPropertyAnimation(this, "windowOpacity"));
    ami2 = QSharedPointer<QPropertyAnimation>(new QPropertyAnimation(this, "geometry"));
    amiGroup = QSharedPointer<QParallelAnimationGroup>(new QParallelAnimationGroup(this));
    amiGroup->addAnimation(ami1.get());
    amiGroup->addAnimation(ami2.get());
    setWindowFlags(windowFlags()| Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(windowFlags()&~ Qt::WindowMinimizeButtonHint);
    mShowSize = QSize(400, 300);
}

FrameWork::~FrameWork()
{

}

void FrameWork::closeEvent(QCloseEvent *e)
{
    e->ignore();
    QRect parentGeo = mParent->geometry();
    int sX = parentGeo.x() + parentGeo.width() / 2;
    int sY = parentGeo.y() + parentGeo.height() / 2;
    int eX = sX - mShowSize.width() / 2;
    int eY = sY - mShowSize.height() / 2;
    ami1->setDuration(200);
    ami1->setStartValue(1);
    ami1->setEndValue(0);
    ami2->setStartValue(QRect(eX, eY, mShowSize.width(), mShowSize.height()));
    ami2->setEndValue(QRect(sX, sY, 0, 0));
    ami2->setEasingCurve(QEasingCurve::InBack);
    ami2->setDuration(200);
    amiGroup->start();
    connect(amiGroup.get(), &QParallelAnimationGroup::finished, this, [=](){
        hide();
        disconnect(amiGroup.get(), &QParallelAnimationGroup::finished, this, 0);
    });
}

void FrameWork::showEvent(QShowEvent *event)
{
    QRect parentGeo = mParent->geometry();
    int sX = parentGeo.x() + parentGeo.width() / 2;
    int sY = parentGeo.y() + parentGeo.height() / 2;
    int eX = sX - mShowSize.width() / 2;
    int eY = sY - mShowSize.height() / 2;
    ami1->setDuration(200);
    ami1->setStartValue(0);
    ami1->setEndValue(1);
    ami2->setStartValue(QRect(sX, sY, 0, 0));
    ami2->setEndValue(QRect(eX, eY, mShowSize.width(), mShowSize.height()));
    ami2->setEasingCurve(QEasingCurve::OutElastic);
    ami2->setDuration(200);
    amiGroup->start();
}

void FrameWork::resizeEvent(QResizeEvent *event)
{
//    mShowSize = event->size();
    QWidget::resizeEvent(event);
}


