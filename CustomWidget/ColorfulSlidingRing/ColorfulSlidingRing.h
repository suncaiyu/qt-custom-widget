#ifndef COLORFULSLIDINGRING_H
#define COLORFULSLIDINGRING_H
#include <QWidget>

class ColorfulSlidingRing : public QWidget
{
    Q_OBJECT
public:
    ColorfulSlidingRing(QWidget *parent = nullptr);
    ~ColorfulSlidingRing();
protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
private:
    QPoint pressPos;
    bool isPressed;
    double ballAngle{0};
};

#endif // COLORFULSLIDINGRING_H
