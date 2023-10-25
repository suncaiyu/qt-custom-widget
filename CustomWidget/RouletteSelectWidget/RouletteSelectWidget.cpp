#include "RouletteSelectWidget.h"
#include <QPainter>
#include <math.h>
#include <QtMath>
#include <QMouseEvent>
#include <QDebug>
#include <FontAwesomeHelper.h>

namespace  {
constexpr int INNER_RADIUS = 30;
constexpr int LAYER_RADIUS = 60;
const qreal PI = qAcos(-1.0f);
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
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setRenderHint(QPainter::SmoothPixmapTransform,true);
    DrawLayer(p);
//    // 内圆
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
            // 这里是从360度，等分的，要是不想布局360，可以适当修改
            qreal angle = (qreal)360 / (qreal)mLayerAreaCount[j];
            path.moveTo(width() / 2, height() / 2);
            // arcTo的参数 1， 外接矩形， 2开始角度，以十字坐标系X轴正方向位0， 3，要画多少度
            // 这里从-30度位置开始画
            path.arcTo(FirstLayerCircumscribedRectangle, i * angle, angle);
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
            mp.iconAngle = i * angle + angle / qreal(2);
            layerSelectedPath.append(mp);
        }
        mLayersSelectPath.append(layerSelectedPath);
    }
}

void RouletteSelectWidget::DrawInner(QPainter &p)
{
    p.fillPath(mInnerPath, Qt::white);
}

/**
 * @brief 计算一个点绕着另一个点旋转一定角度后的坐标位置
 * @param point 要旋转的点（所谓的一个点）
 * @param ori 被围绕的点(另一个点，原点)
 * @param angleDegree 角度
 * @return QPoint 新的坐标
 **/

QPoint rotatePoint(const QPoint &point, const QPoint &ori,double angleDegree) {
    double angleRad = qDegreesToRadians(angleDegree);

    int x = (point.x() - ori.x()) * qCos(angleRad) - (point.y() - ori.y()) * qSin(angleRad) + ori.x();
    int y = (point.x() - ori.x()) * qSin(angleRad) + (point.y() - ori.y()) * qCos(angleRad) + ori.y();

    return QPoint(x, y);
}

void RouletteSelectWidget::DrawLayer(QPainter &p)
{

    for (int j = mLayerCount - 1; j >= 0; --j) {
        int firstLayerRadius = INNER_RADIUS + (LAYER_RADIUS * (j + 1));
        int startRadius = firstLayerRadius;
        int endRadius = firstLayerRadius - LAYER_RADIUS;
        QRect circumscribedRectangle(width() / 2 - firstLayerRadius, height() / 2 - firstLayerRadius,
                                               firstLayerRadius * 2, firstLayerRadius * 2);
        p.save();
        QPainterPath pp;
        pp.addEllipse(circumscribedRectangle);
        p.fillPath(pp, QColor(122, 122, 122));
        p.restore();
        for (int i = 0; i < mLayersSelectPath[j].size() ; ++i) {
            p.save();
            if (mLayersSelectPath[j][i].mPressed) {
                p.setBrush(Qt::red);
            } else
            if (mLayersSelectPath[j][i].mHovered) {
                p.setBrush(Qt::green);
            }
            QPen pen;
            pen.setColor(Qt::white);
            p.setPen(pen);
            p.drawPath(mLayersSelectPath[j].at(i).mPath/*, QColor(133, 133, 133)*/);
            p.restore();


            FontAwesomeHelper *helper = FontAwesomeHelper::GetInstance();
            QString s = helper->mIconUnicodeMap.keys().at(i * j + i);
            p.save();
            QFont font = helper->GetAwesomeFont();
            font.setPointSize(20);
            p.setFont(font);
            pen.setColor(Qt::white);
            p.setPen(pen);
            // 方法1 ： 这种方式用了rotate，图标也会旋转，步美
//            QRect lrect(endRadius, - LAYER_RADIUS / 2, LAYER_RADIUS, LAYER_RADIUS);
//            p.translate(height() / 2, height() / 2);
//            p.rotate(-mLayersSelectPath[j][i].iconAngle);
//            p.drawText(lrect, Qt::AlignCenter, helper->IconUnicode(s));

               // 方法2 ： 用三角函数计算旋转后的位置，不用旋转，美
            QRect lrect(endRadius, - LAYER_RADIUS / 2, LAYER_RADIUS, LAYER_RADIUS);
            QPoint newP = rotatePoint(lrect.center(), QPoint(0, 0), -mLayersSelectPath[j][i].iconAngle);
            lrect = QRect(newP.x() - LAYER_RADIUS / 2, newP.y() - LAYER_RADIUS / 2, LAYER_RADIUS, LAYER_RADIUS);
            p.translate(height() / 2, height() / 2);
//            p.fillRect(lrect, Qt::black);
            p.drawText(lrect, Qt::AlignCenter, helper->IconUnicode(s));

            p.restore();
        }
    }
}
