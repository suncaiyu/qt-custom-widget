#ifndef COLORGRADIENTROUNDEDBUTTON2_H
#define COLORGRADIENTROUNDEDBUTTON2_H

#include <QAbstractButton>
#include <QTimer>

struct doubleColor
{
    doubleColor(QColor frist = Qt::red,QColor second = Qt::blue)
        :fristColor(frist),secondColor(second)
    {}
    QColor fristColor;
    QColor secondColor;

    bool operator !=(const doubleColor & c)
    {
        return (this->fristColor != c.fristColor) || (this->secondColor != c.secondColor);
    }
};
Q_DECLARE_METATYPE(doubleColor)

class ColorGradientRoundedButton2 : public QAbstractButton
{
    Q_OBJECT

public:
    ColorGradientRoundedButton2(QWidget *parent = nullptr);
    ~ColorGradientRoundedButton2()override;

protected:
    void paintEvent(QPaintEvent *event)override;
    void enterEvent(QEvent *event)override;
    void leaveEvent(QEvent *event)override;

private:
    void onTimer();
    doubleColor startColor;
    doubleColor endColor;
    enum class ChangeModel
    {
        Plus,
        Minus
    };
    QTimer timer;
    int rectX{0};
    ChangeModel rectXChangeModel;
};
#endif // COLORGRADIENTROUNDEDBUTTON2_H
