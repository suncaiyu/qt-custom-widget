#ifndef ADSWIDGET2_H
#define ADSWIDGET2_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QMap>
#include <qrect.h>
namespace Ui {
class AdsWidget2;
}

class AdsWidget2 : public QWidget
{
    Q_OBJECT

public:
    enum NavPosition {
        NavPosition_Left = 0,       //左边位置
        NavPosition_Center = 1,     //中间位置
        NavPosition_Right = 2       //右侧位置
    };

    enum NavStyle {
        //里面只完成了两个，还有三个道理是一样的的，但是我不想做了
        NavStyle_Ellipse = 0,       //椭圆条状
        //NavStyle_Circle = 1,        //圆形
        NavStyle_Rect = 2,          //矩形
        //NavStyle_Dot = 3,           //小圆点
        //NavStyle_LongRect = 4       //长条状
    };
    explicit AdsWidget2(QWidget *parent = nullptr);
    ~AdsWidget2();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    void initForm();
    Ui::AdsWidget2 *ui;

    int minHeight; //指示器最小高度
    int minWidth; //指示器最小拉伸宽度
    int maxWidth; //指示器最大拉伸宽度
    int interval; //图片切换间隔,单位毫秒
    int navRadius; //指示器圆角角度
    int maxRadius;
    int minRadius;

    int curRadius;
    int preRadius;

    QList<QString> names; //图片名称集合
    QList<QString> tips; //提示信息集合
    QList<QLabel *> labs; //存储指示器集合
    bool leftToRight; //从左往右切换
    int offset; //图片切换偏移量
    int currentIndex; //当前图片索引
    int previousIndex; //上一张图片索引
    QString qssNormal; //正常状态样式
    QString qssCurrent; //当前状态样式

    QTimer *timer; //定时器切换
    //QHBoxLayout *layout; //指示器所在布局
    //QSpacerItem *spacerLeft; //左侧弹簧
    //QSpacerItem *spacerRight; //右侧弹簧
    int leftandrightspace = 10;
    int topandbottomspace = 10;
    int navspcae = 15;
    void paintNave(QPainter *);
    QWidget *widgetNav; //存放导航指示器的容器

    //动画切换
    QParallelAnimationGroup *animationGroup;
    QPropertyAnimation *animationImage;
    QPropertyAnimation *animationImage2;
    QPropertyAnimation *animationImage3;
    QPropertyAnimation *animationMin;
    QPropertyAnimation *animationMax;

    bool hoverStop; //鼠标悬停停止轮播
    bool showNumber; //是否显示序号

    QColor navColor; //指示器颜色
    QColor textColor; //指示器文字颜色
    QColor tipColor; //提示文字颜色
    QColor darkColor; //当前指示器加深颜色

    QString imageNames; //图片名称
    QString imageTips; //提示信息

    NavPosition navPosition; //指示器位置
    NavStyle navStyle; //指示器样式

    QMap<int, QRect> labMap;

    int currWidth = 6;
    int preWidth;

private slots:
    void changedAds();
    void changedImage(const QVariant &);
    void naveOnClick(int i);
    void changedMax(const QVariant &);
    void changedMin(const QVariant &v);
};

#endif // ADSWIDGET2_H
