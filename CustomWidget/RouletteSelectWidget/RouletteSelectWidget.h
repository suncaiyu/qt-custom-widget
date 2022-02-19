#ifndef ROULETTESELECTWIDGET_H
#define ROULETTESELECTWIDGET_H

#include <QWidget>

class RouletteSelectWidget : public QWidget
{
    Q_OBJECT
    struct MyPath {
        QPainterPath mPath;
        bool mHovered = false;
        bool mPressed = false;
    };

public:
    explicit RouletteSelectWidget(QWidget *parent = nullptr);
    // 有几层， 每层几个按钮 ,至于画按钮，没写，懒
    void SetLayerAndCount(int layercoubt, QList<int> perLayerCount);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    // 准备绘图的数据，改变count等之后可以调用一下
    void Prepare();
    void DrawInner(QPainter &p);
    void DrawLayer(QPainter &p);

    // 内圆的路径，判断是否在内圆上
    QPainterPath mInnerPath;
    // 默认有几个选择区域
    int mLayerCount = 1;
    QList<int> mLayerAreaCount;
    QList<int> mUserSetAreaCount;
    // 各个层级，每个区域的path，判断是否在这些区域上
    QVector<QVector<MyPath>> mLayersSelectPath;
signals:

};

#endif // ROULETTESELECTWIDGET_H
