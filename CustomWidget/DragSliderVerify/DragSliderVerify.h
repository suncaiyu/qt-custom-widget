#ifndef DRAGSLIDERVERIFY_H
#define DRAGSLIDERVERIFY_H

#include <QWidget>

class DragSliderVerify : public QWidget
{
    Q_OBJECT

public:
    DragSliderVerify(QWidget *parent = nullptr);
    ~DragSliderVerify();

protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent *event)override;

private:
    enum class State
    {
        Unverified,
        Verifying,
        Verified
    };
    State verifyState{State::Unverified};
    int sliderX{0};//滑块左上角位置
    QRect sliderRect;
};
#endif // DRAGSLIDERVERIFY_H
