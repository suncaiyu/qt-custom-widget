#ifndef PATTERNCODELOCK_H
#define PATTERNCODELOCK_H

#include <QWidget>
#include <QTimer>

class PatternCodeLockWidget : public QWidget
{
    Q_OBJECT

public:
    PatternCodeLockWidget(int numberOfEachRowAndCol,QWidget *parent = nullptr);
    ~PatternCodeLockWidget()override;
    void reset();

    int getNumberOfEachRowAndCol() const;
    void setNumberOfEachRowAndCol(int newNumberOfEachRowAndCol);

signals:
    void setPassword(QString);

protected:
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;

private:
    void onHoverTimer();
    QString getPassWord();

    enum class CircularState
    {
        normal,//正常
        hoverOnInnerSamrtCircular//鼠标悬浮在中间的小圆上面
    };

    enum class PatternCodeLockState
    {
        notSet,
        setting,
        setted_valid,//有效
        setted_invalid//无效
    };

    int numberOfEachRowAndCol;
    PatternCodeLockState PatternCodeLockSetUpState{PatternCodeLockState::notSet};
    QList<CircularState> circularStateList;
    QList<QRect> smartCircularRectList;
    bool isUpdateSmartCircularRect{true};
    QTimer hoverTimer;
    int radiu;
    int lastHoverIndex{-1};
    int currentchangeLength;
    bool mouseInSomeSmartCircular{false};
    QList<int> setList;
    QPoint settingMousPos;
};
#endif // PATTERNCODELOCK_H
