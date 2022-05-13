#ifndef ROTATINGCARD_H
#define ROTATINGCARD_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>

class RotatingCard : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal cardAngleX READ CardAngleX WRITE SetCardAngleX)
    Q_PROPERTY(qreal cardAngleY READ CardAngleY WRITE SetCardAngleY)
public:
    RotatingCard(QWidget *parent = 0);
    ~RotatingCard();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    struct Card{
        QSize mSize = QSize(321, 428);
        QPoint mStartPoint;
        QPixmap mPixmap = QPixmap(":/liujimin.jpg");
        qreal angleX = 0.0;
        qreal angleY = 0.0;
        qreal maxAngle = 30.0;
    }mCard;
    QPropertyAnimation animationX;
    QPropertyAnimation animationY;

    qreal CardAngleX();
    qreal CardAngleY();
    void SetCardAngleX(qreal x);
    void SetCardAngleY(qreal y);

};

#endif // ROTATINGCARD_H
