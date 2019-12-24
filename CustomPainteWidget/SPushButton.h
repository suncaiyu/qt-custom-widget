#ifndef SPUSHBUTTON_H
#define SPUSHBUTTON_H
#include <QPushButton>
#include <QPropertyAnimation>

class SPushButton:public QPushButton
{
    Q_PROPERTY(int x1 READ GetX1 WRITE SetX1)
    Q_PROPERTY(int x2 READ GetX2 WRITE SetX2)
    Q_PROPERTY(int x3 READ GetX3 WRITE SetX3)
    Q_OBJECT
public:
    explicit SPushButton(QWidget *parent = nullptr);
    ~SPushButton();

protected:
    void enterEvent(QEvent *); //进入事件
    void leaveEvent(QEvent *); //离开事件
    void paintEvent(QPaintEvent *) override;

signals:
    void XChange();

public slots:
    void Printf();

private:
    QPropertyAnimation *m_enteranimation;
    QPropertyAnimation *m_leaveanimation;
    QPropertyAnimation *m_enteranimation2;
    QPropertyAnimation *m_leaveanimation2;
    QPropertyAnimation *m_enteranimation3;
    QPropertyAnimation *m_leaveanimation3;
    int GetX1();
    void SetX1(int xx1);
    int GetX2();
    void SetX2(int xx1);
    int GetX3();
    void SetX3(int xx1);
    int x1;
    int x2;
    int x3;
    int btemp;
    int rtemp;
    QColor myColor;
};

#endif // SPUSHBUTTON_H
