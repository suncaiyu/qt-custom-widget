#ifndef ANIMATEDCHECKBOX_H
#define ANIMATEDCHECKBOX_H
#include <QCheckBox>

// 这个是用stylesheet做的，其实本质是用QStyle做的  可以参考https://blog.csdn.net/qq_33154343/article/details/104987446
// 也可以直接用QPainter画，这个太简单就不演示了
class QLabel;
class AnimatedCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit AnimatedCheckBox(QWidget *parent = nullptr);
    virtual ~AnimatedCheckBox();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    QSize sizeHint() const override;

private:
    std::shared_ptr<QLabel>mIndicator;
};

#endif // ANIMATEDCHECKBOX_H
