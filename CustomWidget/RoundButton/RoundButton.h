#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H
#include <QPushButton>
#include <QWidget>
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
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    void enterEvent(QEnterEvent *e) override;
#else
    void enterEvent(QEvent *e) override;
#endif
    void leaveEvent(QEvent *e)override;

private:
    std::shared_ptr<QGraphicsDropShadowEffect> mShadow;
    QStyleOptionButton mOption;
    QColor mBackColor;
    QColor mLighterColor;
    QColor mOriginColor;
};

#endif // ROUNDBUTTON_H
