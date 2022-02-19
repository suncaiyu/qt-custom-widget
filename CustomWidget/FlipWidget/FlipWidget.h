#ifndef FLIPWIDGET_H
#define FLIPWIDGET_H
#include <QStackedWidget>
#include <QPropertyAnimation>

class FlipWidget : public QStackedWidget
{
    Q_OBJECT
public:
    FlipWidget(QWidget *parent = nullptr);
    virtual ~FlipWidget();
    void SetWidgets(QWidget *w1, QWidget *w2);

protected:
    void paintEvent(QPaintEvent *e)override;

private:
    bool mIsFliping = false;
    QSharedPointer<QPropertyAnimation> mAnimation;
public slots:
    void StartFlip();
    void FlipFinish();
};

#endif // FLIPWIDGET_H
