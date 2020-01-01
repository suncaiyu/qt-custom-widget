#include "AdsWidget2.h"
#include "ui_AdsWidget2.h"
#include <QPainter>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <QMouseEvent>

AdsWidget2::AdsWidget2(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::AdsWidget2)
{
    ui->setupUi(this);
    initForm();
    names << ":/1.jpg"
          << ":/2.jpg"
          << ":/3.jpg"
          << ":/4.jpg";
    tips << "1"
         << "2"
         << "3"
         << "4";
    timer->start();
}

AdsWidget2::~AdsWidget2()
{
    delete ui;
}

void AdsWidget2::paintEvent(QPaintEvent *)
{
    if (names.count() == 0) {
        return;
    }

    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    painter.setPen(tipColor);

    //设置字体
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);

    //取出上一张图片+当前图片,并平滑缩放
    QPixmap previousPix(names.at(previousIndex));
    QPixmap currentPix(names.at(currentIndex));
    previousPix = previousPix.scaled(width,
                                     height,
                                     Qt::KeepAspectRatioByExpanding,
                                     Qt::SmoothTransformation);
    currentPix = currentPix.scaled(width,
                                   height,
                                   Qt::KeepAspectRatioByExpanding,
                                   Qt::SmoothTransformation);
    // offset - > 0 ->600
    int widthOffset = offset + width;
    if (leftToRight == false) {
        widthOffset = offset - width;
    }
    //绘制上一张图片
    painter.drawPixmap(offset, 0, previousPix);
    //绘制当前图片
    painter.drawPixmap(widthOffset, 0, currentPix);

    //绘制上一张图片提示信息,有可能上一张图片提示信息为空
    if (previousIndex <= tips.count() - 1) {
        painter.drawText(QRect(offset + 10, height - minHeight - 40, width - 20, 30),
                         tips.at(previousIndex),
                         option);
    }

    //绘制当前图片提示信息,有可能当前图片提示信息为空
    if (currentIndex <= tips.count() - 1) {
        painter.drawText(QRect(widthOffset + 10, height - minHeight - 40, width - 20, 30),
                         tips.at(currentIndex),
                         option);
    }
    paintNave(&painter);
}

void AdsWidget2::initForm()
{
    hoverStop = true;
    showNumber = false;

    minHeight = 6;
    minWidth = 6;
    maxWidth = 25;
    interval = 3000;
    navRadius = 3;
    maxRadius = 80;
    minRadius = 45;

    navColor = QColor(220, 220, 220);
    textColor = QColor(20, 20, 20);
    tipColor = QColor(255, 255, 255);
    darkColor = QColor(255, 255, 255);

    imageNames.clear();
    imageTips.clear();

    navPosition = NavPosition_Left;
    navStyle = NavStyle_Ellipse;

    leftToRight = true;
    offset = 0;
    currentIndex = 0;
    previousIndex = 0;

    //定时器切换图片
    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(changedAds()));

    this->setMouseTracking(true);

    //定义动画组
    animationGroup = new QParallelAnimationGroup();

    //定义动画切换图片
    animationImage = new QPropertyAnimation(this, "");
    connect(animationImage,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(changedImage(const QVariant &)));
    animationImage->setEasingCurve(QEasingCurve::OutCirc);
    animationImage->setDuration(1000);
    animationGroup->addAnimation(animationImage);

    QSequentialAnimationGroup *sequentialGroup = new QSequentialAnimationGroup();

    //用于切换最小拉伸宽度
    animationMin = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMin,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(changedMin(const QVariant &)));
    animationMin->setEasingCurve(QEasingCurve::OutCubic);
    animationMin->setDuration(500);


    //用于切换最大拉伸宽度
    animationMax = new QPropertyAnimation(sequentialGroup, "");
    connect(animationMax,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(changedMax(const QVariant &)));
    animationMax->setEasingCurve(QEasingCurve::OutCubic);
    animationMax->setDuration(500);


    //按钮切换串行运行
    sequentialGroup->addAnimation(animationMin);
    sequentialGroup->addAnimation(animationMax);

    animationGroup->addAnimation(sequentialGroup);
}

void AdsWidget2::changedAds()
{
    if (names.count() == 0) {
        return;
    }
    previousIndex = currentIndex;
    if (currentIndex < names.count() - 1) {
        currentIndex++;
        leftToRight = true;
    } else {
        currentIndex = 0;
        leftToRight = false;
    }

    if (leftToRight) {
        animationImage->setStartValue(0);
        animationImage->setEndValue(0 - width());
    }
    else {
        animationImage->setStartValue(0);
        animationImage->setEndValue(width());
    }
    animationMax->setStartValue(minWidth);
    animationMax->setEndValue(maxWidth);
    animationMin->setStartValue(maxWidth);
    animationMin->setEndValue(minWidth);

    currWidth = minWidth;
    preWidth = maxWidth;
    animationGroup->start();
}

void AdsWidget2::changedImage(const QVariant &v)
{
    offset = v.toInt();
    update();
}

void AdsWidget2::paintNave(QPainter *painter)
{
    labMap.clear();
    if (navStyle == NavStyle_Rect) {
        int height = this->height();
        int paintX;
        int startX;
        //指示器的总长度
        int totalX = navspcae * (names.count() - 1) + maxWidth * (names.count());
        // 当现实在左边是
        if (navPosition == NavPosition_Left) {
            for (int i = 0; i < names.count(); i++) {
                paintX = leftandrightspace + navspcae * (i + 1) + maxWidth * i;
                QRect firstnave = QRect(paintX, height - minHeight - topandbottomspace, maxWidth, minHeight);
                labMap.insert(i, firstnave);
                if (i == currentIndex) {
                    painter->fillRect(firstnave, darkColor);
                }
                else {
                    painter->fillRect(firstnave, navColor);
                }
            }
        }

        if (navPosition == NavPosition_Center) {
            startX = width() / 2 - totalX / 2;
            for (int i = 0; i < names.count(); i++) {
                paintX = navspcae * (i + 1) + maxWidth * i + startX;
                QRect firstnave = QRect(paintX, height - minHeight - topandbottomspace, maxWidth, minHeight);
                labMap.insert(i, firstnave);
                if (i == currentIndex) {
                    painter->fillRect(firstnave, darkColor);
                }
                else {
                    painter->fillRect(firstnave, navColor);
                }
            }
        }
        if (navPosition == NavPosition_Right) {
            startX = width() - totalX - leftandrightspace;
            for (int i = 0; i < names.count(); i++) {
                paintX = navspcae * (i + 1) + maxWidth * i + startX;
                QRect firstnave = QRect(paintX, height - minHeight - topandbottomspace, maxWidth, minHeight);
                labMap.insert(i, firstnave);
                if (i == currentIndex) {
                    painter->fillRect(firstnave, darkColor);
                }
                else {
                    painter->fillRect(firstnave, navColor);
                }
            }
        }
    }

    if (navStyle == NavStyle_Ellipse) {
        if (navPosition == NavPosition_Left) {
            int paintX;
            for (int i = 0; i < names.length(); i++) {
                if (currentIndex >= i) {
                    paintX = leftandrightspace + navspcae * (i) + minWidth * i;
                }
                if (currentIndex < i) {
                    paintX = leftandrightspace + navspcae * (i) + (minWidth * (i - 1)) + 25;
                }
                if (currentIndex == i) {
                    if (currentIndex == previousIndex) {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        labMap.insert(i, firstRect);
                        QPainterPath path;
                        path.addRoundRect(firstRect, maxRadius, maxRadius);
                        painter->fillPath(path, darkColor);
                    }
                    else {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        labMap.insert(i, firstRect);
                        QPainterPath path;
                        path.addRoundRect(firstRect, minRadius, minRadius);
                        painter->fillPath(path, darkColor);
                    }
                }
                else if (i == previousIndex) {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, preWidth, minHeight);
                    labMap.insert(i, firstRect);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, darkColor);
                }
                else {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, minWidth, minHeight);
                    labMap.insert(i, firstRect);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, navColor);
                }
            }
        }

        if (navPosition == NavPosition_Center) {
            int totalX = navspcae * (names.count() - 1) + minWidth * (names.count() - 1) + maxWidth;
            int paintX;
            int startX = width() / 2 - totalX / 2;
            for (int i = 0; i < names.length(); i++) {
                if (currentIndex >= i) {
                    paintX = startX + navspcae * (i) + minWidth * i;
                }
                if (currentIndex < i) {
                    paintX = startX + navspcae * (i) + (minWidth * (i - 1)) + 25;
                }
                if (currentIndex == i) {
                    if (currentIndex == previousIndex) {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        QPainterPath path;
                        path.addRoundRect(firstRect, maxRadius, maxRadius);
                        painter->fillPath(path, darkColor);
                    }
                    else {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        QPainterPath path;
                        path.addRoundRect(firstRect, minRadius, minRadius);
                        painter->fillPath(path, darkColor);
                    }
                }
                else if (i == previousIndex) {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, preWidth, minHeight);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, darkColor);
                }
                else {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, minWidth, minHeight);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, navColor);
                }
            }
        }

        if (navPosition == NavPosition_Right) {
            int totalX = navspcae * (names.count() - 1) + minWidth * (names.count() - 1) + maxWidth;
            int paintX;
            int startX = width() - totalX - leftandrightspace;
            for (int i = 0; i < names.length(); i++) {
                if (currentIndex >= i) {
                    paintX = startX + navspcae * (i)+minWidth * i;
                }
                if (currentIndex < i) {
                    paintX = startX + navspcae * (i)+(minWidth * (i - 1)) + 25;
                }
                if (currentIndex == i) {
                    if (currentIndex == previousIndex) {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        QPainterPath path;
                        path.addRoundRect(firstRect, maxRadius, maxRadius);
                        painter->fillPath(path, darkColor);
                    }
                    else {
                        QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, currWidth, minHeight);
                        QPainterPath path;
                        path.addRoundRect(firstRect, minRadius, minRadius);
                        painter->fillPath(path, darkColor);
                    }
                }
                else if (i == previousIndex) {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, preWidth, minHeight);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, darkColor);
                }
                else {
                    QRect firstRect = QRect(paintX, height() - minHeight - topandbottomspace, minWidth, minHeight);
                    QPainterPath path;
                    path.addRoundRect(firstRect, maxRadius, maxRadius);
                    painter->fillPath(path, navColor);
                }
            }
        }
    }
}
#include <qdebug.h>
void AdsWidget2::mousePressEvent(QMouseEvent *e)
{
    for (int i = 0; i < labMap.size(); i++) {
        if (labMap[i].contains(e->pos())) {
            naveOnClick(i);
        }
    }
}

void AdsWidget2::naveOnClick(int i)
{
    if (animationGroup->state() == QAbstractAnimation::Running) {
        animationGroup->stop();
    }
    previousIndex = currentIndex;
    currentIndex = i;
    if (currentIndex > previousIndex) {
        leftToRight = true;
    }
    if (currentIndex < previousIndex) {
        leftToRight = false;
    }
    if (currentIndex == previousIndex) {
        return;
    }
    if (leftToRight) {
        animationImage->setStartValue(0);
        animationImage->setEndValue(0 - width());
    }
    else {
        animationImage->setStartValue(0);
        animationImage->setEndValue(width());
    }

    animationMax->setStartValue(minWidth);
    animationMax->setEndValue(maxWidth);
    animationMin->setStartValue(maxWidth);
    animationMin->setEndValue(minWidth);

    currWidth = minWidth;
    preWidth = maxWidth;
    animationGroup->start();
}

void AdsWidget2::enterEvent(QEvent *event)
{
    timer->stop();
}

void AdsWidget2::leaveEvent(QEvent *event)
{
    timer->start(interval);
}

void AdsWidget2::changedMax(const QVariant &v)
{
    currWidth = v.toInt();
    update();
}

void AdsWidget2::changedMin(const QVariant &v)
{
    preWidth = v.toInt();
    update();
}
