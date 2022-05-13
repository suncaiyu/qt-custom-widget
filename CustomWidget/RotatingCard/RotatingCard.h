#ifndef ROTATINGCARD_H
#define ROTATINGCARD_H

#include <QWidget>

class RotatingCard : public QWidget
{
    Q_OBJECT
public:
    RotatingCard(QWidget *parent = 0);
    ~RotatingCard();

private:
    struct Card{
        QSize mSize;
        QPoint mStartPoint;
        QPixmap mPixmap;
    }mCard;

};

#endif // ROTATINGCARD_H
