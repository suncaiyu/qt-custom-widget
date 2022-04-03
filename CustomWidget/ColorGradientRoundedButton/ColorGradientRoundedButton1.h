#ifndef COLORGRADIENTROUNDEDBUTTON1_H
#define COLORGRADIENTROUNDEDBUTTON1_H

#include <QAbstractButton>

struct doubleColor1
{
    doubleColor1(QColor frist = Qt::red,QColor second = Qt::blue)
        :fristColor(frist),secondColor(second)
    {}
    QColor fristColor;
    QColor secondColor;

    bool operator !=(const doubleColor1 & c)
    {
        return (this->fristColor != c.fristColor) || (this->secondColor != c.secondColor);
    }
};
Q_DECLARE_METATYPE(doubleColor1)

class ColorGradientRoundedButton1 : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(doubleColor1 currentColor MEMBER currentColor)
public:
    ColorGradientRoundedButton1(QWidget *parent = nullptr);
    ~ColorGradientRoundedButton1()override;

protected:
    void paintEvent(QPaintEvent *event)override;
    void enterEvent(QEvent *event)override;
    void leaveEvent(QEvent *event)override;

private:
    void onValueChanged(const QVariant &value);
    doubleColor1 currentColor;
    doubleColor1 startColor;
    doubleColor1 endColor;
    class QPropertyAnimation * animation{nullptr};
};
#endif // COLORGRADIENTROUNDEDBUTTON1_H
