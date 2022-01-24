#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QStyleOptionButton>

class RoundButton : public QPushButton
{
public:
    RoundButton(QWidget *parent = nullptr);
    RoundButton(QString str, QWidget *parent = nullptr);
    virtual ~RoundButton();
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
    void enterEvent(QEvent *e)override;
    void leaveEvent(QEvent *e)override;

private:
    std::shared_ptr<QGraphicsDropShadowEffect> mShadow;
    QStyleOptionButton mOption;
    QColor mBackColor;
    QColor mLighterColor;
    QColor mOriginColor;
};

#endif // ROUNDBUTTON_H
