#include "ImageViewLabel.h"

//重写QLabel控件
#include <QPushButton>
#include <QButtonGroup>
#include <QPainter>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QTimer>

const int btn_expand_width = 24; //按钮拉伸宽度
const int btn_shrik_width = 6; //按钮收缩宽度

ImageViewLabel::ImageViewLabel(QWidget *parent)
    : QLabel(parent), m_offset(0), m_curIndex(0), m_preIndex(0), m_blefttoright(true)
{
    setMinimumSize(120, 240);

    m_btnGroup = new QButtonGroup(this);
    connect(m_btnGroup, SIGNAL(buttonClicked(int)), SLOT(onbuttonClicked(int)));

    m_btnParalGroup = new QParallelAnimationGroup(this);
    m_imageAnimation = new QPropertyAnimation(m_btnParalGroup, "");
    m_imageAnimation->setEasingCurve(QEasingCurve::OutCirc);
    m_imageAnimation->setDuration(800);
    connect(m_imageAnimation,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(onImagevalueChanged(const QVariant &)));

    QSequentialAnimationGroup *sequentialGroup = new QSequentialAnimationGroup(m_btnParalGroup);
    m_btnExpAnimation = new QPropertyAnimation(sequentialGroup, "");
    m_btnExpAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_btnExpAnimation,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(onBtnExpvalueChanged(const QVariant &)));
    m_btnExpAnimation->setDuration(400);

    m_btnShrikAnimation = new QPropertyAnimation(sequentialGroup, "");
    m_btnShrikAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_btnShrikAnimation,
            SIGNAL(valueChanged(const QVariant &)),
            this,
            SLOT(onBtnShrikvalueChanged(const QVariant &)));
    m_btnShrikAnimation->setDuration(400);

    //按钮切换串行运行
    sequentialGroup->addAnimation(m_btnExpAnimation);
    sequentialGroup->addAnimation(m_btnShrikAnimation);

    //图片切换与按钮切换并行运行
    m_btnParalGroup->addAnimation(m_imageAnimation);
    m_btnParalGroup->addAnimation(sequentialGroup);

    initControl();
}

ImageViewLabel::~ImageViewLabel() {}

void ImageViewLabel::initControl()
{
    m_horizontalLayoutWidget = new QWidget(this);
    m_horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    m_switchBtnLayout = new QHBoxLayout(m_horizontalLayoutWidget);
    m_switchBtnLayout->setSpacing(12);
    m_switchBtnLayout->setContentsMargins(0, 0, 0, 0);

    m_imageTimer = new QTimer(this);
    m_imageTimer->setInterval(2000);
    connect(m_imageTimer, &QTimer::timeout, this, &ImageViewLabel::onImageShowTimeOut);
    m_imageTimer->start();
}

void ImageViewLabel::onImagevalueChanged(const QVariant &variant)
{
    m_offset = variant.toInt();
    update();
}

void ImageViewLabel::onBtnExpvalueChanged(const QVariant &variant)
{
    m_btnGroup->button(m_curIndex)->setFixedWidth(variant.toInt());
}

void ImageViewLabel::onBtnShrikvalueChanged(const QVariant &variant)
{
    for (int index = 0; index < m_imagepathpairlst.size(); index++) {
        if (m_curIndex != index && m_btnGroup->button(index)->width() > btn_shrik_width) {
            m_btnGroup->button(index)->setFixedWidth(variant.toInt());
        }
    }
}

void ImageViewLabel::onbuttonClicked(int index)
{
    if (m_curIndex == index) {
        return;
    }
    if (index < 0) {
        index = m_imagepathpairlst.size() - 1;
    }
    if (index >= m_imagepathpairlst.size()) {
        index = 0;
    }

    m_preIndex = m_curIndex;
    m_curIndex = index;
    //图片切换
    if (m_preIndex < m_curIndex) {
        //向左滑
        m_imageAnimation->setStartValue(0);
        m_imageAnimation->setEndValue(0 - width());
        m_blefttoright = false;
    } else {
        //向右滑
        m_imageAnimation->setStartValue(0);
        m_imageAnimation->setEndValue(width());
        m_blefttoright = true;
    }
    //按钮切换
    m_btnShrikAnimation->setStartValue(btn_expand_width);
    m_btnShrikAnimation->setEndValue(btn_shrik_width);

    m_btnExpAnimation->setStartValue(btn_shrik_width);
    m_btnExpAnimation->setEndValue(btn_expand_width);

    m_imageTimer->start(2000);
    m_btnParalGroup->start();
}

void ImageViewLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
    painter.setPen(QColor(210, 210, 210, 200));
    QFont font = painter.font();
    font.setFamily(QString::fromLocal8Bit("微软雅黑"));
    font.setBold(true);
    font.setPixelSize(18);
    painter.setFont(font);

    if (m_blefttoright) {
        painter.drawPixmap(m_offset,
                           0,
                           QPixmap(m_imagepathpairlst.at(m_preIndex).first)
                               .scaled(width(),
                                       height(),
                                       Qt::KeepAspectRatioByExpanding,
                                       Qt::SmoothTransformation));
        painter.drawPixmap(m_offset - width(),
                           0,
                           QPixmap(m_imagepathpairlst.at(m_curIndex).first)
                               .scaled(width(),
                                       height(),
                                       Qt::KeepAspectRatioByExpanding,
                                       Qt::SmoothTransformation));

        painter.drawText(QRect(m_offset + 12, height() - 52, width(), 32),
                         m_imagepathpairlst.at(m_preIndex).second,
                         option);
        painter.drawText(QRect(m_offset - width() + 12, height() - 52, width(), 32),
                         m_imagepathpairlst.at(m_curIndex).second,
                         option);
    } else {
        painter.drawPixmap(m_offset,
                           0,
                           QPixmap(m_imagepathpairlst.at(m_preIndex).first)
                               .scaled(width(),
                                       height(),
                                       Qt::KeepAspectRatioByExpanding,
                                       Qt::SmoothTransformation));
        painter.drawPixmap(m_offset + width(),
                           0,
                           QPixmap(m_imagepathpairlst.at(m_curIndex).first)
                               .scaled(width(),
                                       height(),
                                       Qt::KeepAspectRatioByExpanding,
                                       Qt::SmoothTransformation));

        painter.drawText(QRect(m_offset + 12, height() - 52, width(), 32),
                         m_imagepathpairlst.at(m_preIndex).second,
                         option);
        painter.drawText(QRect(m_offset + width() + 12, height() - 52, width(), 32),
                         m_imagepathpairlst.at(m_curIndex).second,
                         option);
    }
}

void ImageViewLabel::resizeEvent(QResizeEvent *event)
{
    m_horizontalLayoutWidget->setGeometry(QRect(12, height() - 18, width() - 24, 6));
    QLabel::resizeEvent(event);
}

void ImageViewLabel::enterEvent(QEvent *event)
{
    m_imageTimer->stop();
}

void ImageViewLabel::leaveEvent(QEvent *event)
{
    m_imageTimer->start(2000);
}

void ImageViewLabel::addImage(const QList<std::pair<QString, QString>>& imagepathpairlst)
{
    m_imagepathpairlst = imagepathpairlst;
    for (int index = 0; index < imagepathpairlst.size(); index++)
    {
        QPushButton* btn = new QPushButton(m_horizontalLayoutWidget);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setFixedSize(btn_shrik_width, btn_shrik_width);
        btn->setStyleSheet("QPushButton{border-image:url(:/ImageViewPager/Resources/point.png);border-width:0 3px;}");
        m_btnGroup->addButton(btn, index);
        m_switchBtnLayout->addWidget(btn);
    }
    m_switchBtnLayout->addStretch();
    m_btnGroup->button(m_curIndex)->setFixedWidth(btn_expand_width);
    update();
}

void ImageViewLabel::onImageShowTimeOut()
{
    onbuttonClicked(m_curIndex + 1);
}
