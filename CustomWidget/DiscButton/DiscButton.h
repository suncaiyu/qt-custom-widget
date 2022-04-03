#ifndef DISCBUTTON_H
#define DISCBUTTON_H
#include <QWidget>

class DiscButton : public QWidget
{
    Q_OBJECT
public:
    DiscButton(QWidget *parent = nullptr);
    ~DiscButton();

signals:
    void selectColor(QString colorString);

protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;

private:
    bool isPointInCir(const QPoint &point, const QRect &rect);
    QRectF drawRect;//整个大圆的范围
    QPainterPath fanShaped[4];
    QRectF centerCircularRect;//中心圆按钮的范围
    QPainterPath gradientArc(double startAngle, double angleLength, double arcHeight);
    enum class pressBtnType //按下的是哪个按钮
    {
        up = 0,
        left,
        down,
        right,
        center,
        None
    };
    pressBtnType pressedBtn{pressBtnType::None};
};

#endif // DISCBUTTON_H
