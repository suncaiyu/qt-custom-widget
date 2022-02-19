#include "RouletteSelectWidget.h"
#include <QPainter>
#include <math.h>
#include <QMouseEvent>
#include <QDebug>
#include <FontAwesomeHelper.h>

namespace  {
constexpr int INNER_RADIUS = 30;
constexpr int LAYER_RADIUS = 60;
}
RouletteSelectWidget::RouletteSelectWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    mUserSetAreaCount.clear();
}

void RouletteSelectWidget::SetLayerAndCount(int layercount, QList<int> perLayerCount)
{
    mLayerCount = layercount;
    mUserSetAreaCount = perLayerCount;
    Prepare();
}

void RouletteSelectWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,  true);
    DrawLayer(p);
    // 内圆
    DrawInner(p);
}

void RouletteSelectWidget::resizeEvent(QResizeEvent *event)
{
    Prepare();
    update();
}

void RouletteSelectWidget::mouseMoveEvent(QMouseEvent *e)
{
    for (int j = 0; j < mLayerCount; ++j) {
        for (int i = 0; i < mLayersSelectPath[j].size(); ++i) {
            if (mLayersSelectPath[j].at(i).mPath.contains(e->pos())) {
                mLayersSelectPath[j][i].mHovered = true;
            } else {
                mLayersSelectPath[j][i].mHovered = false;
            }
        }
    }
    update();
}

void RouletteSelectWidget::mousePressEvent(QMouseEvent *e)
{
    for (int j = 0; j < mLayerCount; ++j) {
        for (int i = 0; i < mLayersSelectPath[j].size(); ++i) {
            if (mLayersSelectPath[j].at(i).mPath.contains(e->pos())) {
                mLayersSelectPath[j][i].mPressed = true;
                qDebug() << QString("you pressed %1 layer %2 count").arg(j).arg(i);
            } else {
                mLayersSelectPath[j][i].mPressed = false;
            }
        }
    }
    update();
}

void RouletteSelectWidget::mouseReleaseEvent(QMouseEvent *event)
{
    for (int j = 0; j < mLayerCount; ++j) {
        for (int i = 0; i < mLayersSelectPath[j].size(); ++i) {
            mLayersSelectPath[j][i].mPressed = false;
        }
    }
    update();
}

void RouletteSelectWidget::Prepare()
{
    mLayerAreaCount.clear();
    mInnerPath.clear();
    mLayersSelectPath.clear();
    if (mUserSetAreaCount.size() == 0) {
        for (int i = 0; i < mLayerCount; ++i) {
            mLayerAreaCount.append(3);
        }
    } else {
        mLayerAreaCount = mUserSetAreaCount;
    }
    // 内圆的path
    QRect innerRect(width() / 2 - INNER_RADIUS, height() / 2 - INNER_RADIUS, INNER_RADIUS * 2, INNER_RADIUS * 2);

    mInnerPath.addEllipse(innerRect);
    for (int j = 0; j < mLayerCount; ++j) {
        QVector<MyPath> layerSelectedPath;
        int firstLayerRadius = INNER_RADIUS + (LAYER_RADIUS * (j + 1));
        QRect FirstLayerCircumscribedRectangle(width() / 2 - firstLayerRadius, height() / 2 - firstLayerRadius,
                                               firstLayerRadius * 2, firstLayerRadius * 2);
        for (int i = 0; i < mLayerAreaCount[j]; ++i) {
            QPainterPath path;
            // 这里是从160度，等分的，要是不想布局160，可以适当修改
            int angle = 160 / mLayerAreaCount[j];
            path.moveTo(width() / 2, height() / 2);
            // arcTo的参数 1， 外接矩形， 2开始角度，以十字坐标系X轴正方向位0， 3，要画多少度
            // 这里从-30度位置开始画
            path.arcTo(FirstLayerCircumscribedRectangle, i * angle - 30, angle);
            path.closeSubpath();
            if (j == 0) {
                path = path - mInnerPath;
            } else {
                QPainterPath tmp;
                int radius = LAYER_RADIUS * j + INNER_RADIUS;
                QRect rc(width() / 2 - radius, height() / 2 - radius, radius * 2, radius * 2);
                tmp.addEllipse(rc);
                path = path - tmp;
            }
            MyPath mp;
            mp.mPath = path;
            layerSelectedPath.append(mp);
        }
        mLayersSelectPath.append(layerSelectedPath);
    }
}

void RouletteSelectWidget::DrawInner(QPainter &p)
{
    p.drawPath(mInnerPath);
}

void RouletteSelectWidget::DrawLayer(QPainter &p)
{
    for (int j = mLayerCount - 1; j >= 0; --j) {
        int firstLayerRadius = INNER_RADIUS + (LAYER_RADIUS * (j + 1));
        QRect circumscribedRectangle(width() / 2 - firstLayerRadius, height() / 2 - firstLayerRadius,
                                               firstLayerRadius * 2, firstLayerRadius * 2);
        p.save();
//        p.setBrush(Qt::black);
        p.drawEllipse(circumscribedRectangle);
        p.restore();
        for (int i = 0; i < mLayersSelectPath[j].size() ; ++i) {
            p.save();
            if (mLayersSelectPath[j][i].mPressed) {
                p.setBrush(Qt::red);
            } else
            if (mLayersSelectPath[j][i].mHovered) {
                p.setBrush(Qt::green);
            }
            p.drawPath(mLayersSelectPath[j].at(i).mPath);
            FontAwesomeHelper *helper = FontAwesomeHelper::GetInstance();
            QString s = helper->mIconUnicodeMap.keys().at(i * j + i);
            QFont font = helper->GetAwesomeFont();
            font.setPointSize(20);
            p.setFont(font);
            // 这里的boundingRect可能不准哦，可以自己用其他方式计算一下，图标画在什么位置好
            p.drawText(mLayersSelectPath[j].at(i).mPath.boundingRect(), Qt::AlignCenter, helper->IconUnicode(s));
            p.restore();
        }
    }
}
