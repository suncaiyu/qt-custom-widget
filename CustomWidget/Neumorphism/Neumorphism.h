#ifndef NEUMORPHISM_H
#define NEUMORPHISM_H
#include <QWidget>
#include "HoverWidget.h"
#include <QGraphicsDropShadowEffect>

class Neumorphism : public QWidget
{
    Q_OBJECT
public:
    Neumorphism(QWidget *parent = 0);
    ~Neumorphism();
    void SetFlat(bool f) {mHoverWidget->SetFlat(f);}

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QSharedPointer<HoverWidget> mHoverWidget;
    QSharedPointer<QGraphicsDropShadowEffect> mEffect;
};

#endif // NEUMORPHISM_H
