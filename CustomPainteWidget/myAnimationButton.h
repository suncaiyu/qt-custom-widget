#ifndef MYANIMATIONBUTTON_H
#define MYANIMATIONBUTTON_H

#include <QWidget>


class QPropertyAnimation;

class myAnimationButton : public QWidget
{
    Q_OBJECT

public:
    explicit myAnimationButton(QWidget *parent = 0);
    ~myAnimationButton();

    void enterImageChanged(QVariant value);
    void leaveImageChanged(QVariant value);

    void setImagePath(QString path);
    void setText(QString text){
        this->text = text;
    }
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);


private:

    int imageWidth;
    int imageHeight;

    int originalWidth;
    int originalHeight;

    int newWidth;
    int newHeight;


    QString imagePath;
    QString text;

    QPropertyAnimation* enterAnimation;
    QPropertyAnimation* leaveAnimation;


};

#endif // MYANIMATIONBUTTON_H

