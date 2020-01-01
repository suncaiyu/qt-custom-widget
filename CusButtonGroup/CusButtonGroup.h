#ifndef CUSBUTTONGROUP_H
#define CUSBUTTONGROUP_H

#include <QWidget>
#include <qvariant.h>

namespace Ui {
class CusButtonGroup;
}
class QButtonGroup;
class QPushButton;
class QPropertyAnimation;
class CusButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit CusButtonGroup(QWidget *parent = nullptr);
    ~CusButtonGroup();
    /* 动画条的位置 */
    enum {
        North,    ///>上面
        South,    ///>下面
        East,    ///>右边
        West,    ///>左边
    };
    void setLineHeight(int lineHeight);
    void setButtonPosition(int position);
    void deleteLayout();
    void addButton(QPushButton *btn, int id, int height, QColor b);
    void setButtonColor(QColor color);
    void setDurnation(int);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *e);

private slots:
    void onvalueChanged(QVariant variant);
    void onbuttonClicked(int);
private:
    Ui::CusButtonGroup *ui;

    // 动画持续时间(ms)
    int interval;
    // 设置动画条的位置 
    int m_btnPosition;
    // 当前按钮位置索引
    int m_curIndex;
    // 上一次按钮的位置索引
    int m_preIndex;
    // 滑动动画条的x起点位置
    int m_offset;
    // 滑动动画条的高度
    int m_lineHeight;
    // 滑动动画条的颜色
    QColor m_lineColor;
    // 按钮的group组
    QButtonGroup *m_btnGroup;
    // 属性动画类
    QPropertyAnimation *m_animation;
    // 按钮的size
    QSize m_btnSize;
    // 存放PushButton指针的List
    QList<QPushButton *> m_buttonLst;
};

#endif // CUSBUTTONGROUP_H
