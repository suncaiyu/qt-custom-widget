#include "FlipWidget.h"
#include <QStylePainter>

FlipWidget::FlipWidget(QWidget *parent) : QStackedWidget(parent)
{
    setProperty("flip", 0);
    mAnimation = QSharedPointer<QPropertyAnimation>(new QPropertyAnimation(this, "flip"));
    mAnimation->setEndValue(180);
    mAnimation->setStartValue(0);
    mAnimation->setDuration(1200);
    connect(mAnimation.get(), SIGNAL(finished()), this, SLOT(FlipFinish()));
    connect(mAnimation.get(), SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
}

FlipWidget::~FlipWidget()
{

}

void FlipWidget::SetWidgets(QWidget *w1, QWidget *w2)
{
    addWidget(w1);
    addWidget(w2);
}

void FlipWidget::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this);
    if (mIsFliping) {
        bool ok;
        int value = property("flip").toInt(&ok);
        if (!ok) {
            return;
        }
        if (value <= 90)
        {
            QPixmap rotatePixmap(currentWidget()->size());
            currentWidget()->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(value, Qt::YAxis);
            painter.setTransform(transform);
            // 因为坐标系中心已经translate了  所以需要对应改变起始点,也可以像下面一样
//            painter.drawPixmap(-1 * width() / 2, 0, rotatePixmap);
            painter.drawPixmap(rect().adjusted(-1 * width() / 2, 0, -1 * width() / 2, 0), rotatePixmap);
        }
        // 大于90度时
        else
        {
            QPixmap rotatePixmap(widget(currentIndex() + 1 > 1 ? 0 : 1)->size());
            widget(currentIndex() + 1 > 1 ? 0 : 1)->render(&rotatePixmap);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);
            QTransform transform;
            transform.translate(width() / 2, 0);
            transform.rotate(value + 180, Qt::YAxis);
            // 把偏移的再改回来，就可以正常画了
            transform.translate(-width() / 2, 0);
            painter.setTransform(transform);
            painter.drawPixmap(rect(), rotatePixmap);
        }
    } else {
        QStackedWidget::paintEvent(e);
    }
}

void FlipWidget::FlipFinish()
{
    mIsFliping = false;
    int index = currentIndex();
    setCurrentIndex(index + 1 > 1 ? 0 : 1);
}

void FlipWidget::StartFlip()
{
    if (mIsFliping) {
        return;
    }
    mIsFliping = true;
    widget(currentIndex() + 1 > 1 ? 0 : 1)->resize(currentWidget()->size());
    currentWidget()->hide();
    mAnimation->start();
}
