#include "CusButtonGroup.h"
#include "ui_CusButtonGroup.h"
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QPainter>
#include <QLayout>
#include <QPushButton>
#include <QList>

CusButtonGroup::CusButtonGroup(QWidget *parent)
    : QWidget(parent), m_btnPosition(0), m_curIndex(0), m_preIndex(0), m_offset(0), m_lineHeight(2),
      m_lineColor(QColor(21, 156, 119)), interval(200)
{
    ui->setupUi(this);

    m_btnGroup = new QButtonGroup(this);
    connect(m_btnGroup, SIGNAL(buttonClicked(int)),this, SLOT(onbuttonClicked(int)));

    m_animation = new QPropertyAnimation(this, "");
    m_animation->setDuration(interval);
    connect(m_animation, SIGNAL(valueChanged(QVariant)),this, SLOT(onvalueChanged(QVariant)));

    //默认在上边
    setButtonPosition(CusButtonGroup::North);
}

CusButtonGroup::~CusButtonGroup() {}

/* @brief QPropertyAnimation动画类相关的值变化时，触发的方法
 * @param variant  QPropertyAnimation动画类相关的值
 */
void CusButtonGroup::onvalueChanged(QVariant variant)
{
    m_offset = variant.toInt();
    update();
}

/* @brief 设置滑动线条的高度（宽度）
 * @param lineHeight 线宽/线高
 */
void CusButtonGroup::setLineHeight(int lineHeight)
{
    m_lineHeight = lineHeight;
}


void CusButtonGroup::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_lineColor);
    if (m_btnPosition == CusButtonGroup::North) {
        painter.drawRect(m_offset, 0, m_btnSize.width(), m_lineHeight);
    } else if (m_btnPosition == CusButtonGroup::South) {
        painter.drawRect(m_offset, this->height() - m_lineHeight, m_btnSize.width(), m_lineHeight);
    } else if (m_btnPosition == CusButtonGroup::West) {
        painter.drawRect(0, m_offset, m_lineHeight, m_btnSize.height());
    } else if (m_btnPosition == CusButtonGroup::East) {
        painter.drawRect(this->width() - m_lineHeight, m_offset, m_lineHeight, m_btnSize.height());
    }
}

/* @brief 设置滑动线条的位置以及设置对应的布局
 * @param position 滑动线条的位置
 */
void CusButtonGroup::setButtonPosition(int position)
{
    deleteLayout();
    m_btnPosition = position;
    if (position == CusButtonGroup::North) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, m_lineHeight, 0, 0);
        layout->setSpacing(0);
        setLayout(layout);
    } else if (position == CusButtonGroup::South) {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, m_lineHeight);
        layout->setSpacing(0);
        setLayout(layout);
    } else if (position == CusButtonGroup::West) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(m_lineHeight, 0, 0, 0);
        layout->setSpacing(0);
        setLayout(layout);
    } else if (position == CusButtonGroup::East) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, m_lineHeight, 0);
        layout->setSpacing(0);
        setLayout(layout);
    } else {
        Q_ASSERT(false && "no match position!");
    }
}

/* @brief 添加按钮
 * @param btn 按钮
 * @param id 按钮的别名。id
 * @param buttonheight 按钮的高度
 * @param backgroundColor 按钮的初始背景色
 */
void CusButtonGroup::addButton(QPushButton *btn, int id, int buttonheight, QColor backgroundColor)
{
    m_btnGroup->addButton(btn, id);
    m_buttonLst.append(btn);
    layout()->addWidget(btn);
    m_btnSize = btn->size();
    btn->setFixedHeight(buttonheight);
    this->setFixedHeight(buttonheight + m_lineHeight);
    QString style = QString("QPushButton{background-color:rgb(%4, %5, %6);border:none;}"
                            "QPushButton:hover{background-color:rgba(%1, %2, %3, 40);}"
                            "QPushButton:pressed, QPushButton:checked{background-color:rgba(%1, %2, %3, 80);}").arg(m_lineColor.red()).arg(m_lineColor.green()).arg(m_lineColor.blue()).arg(backgroundColor.red()).arg(backgroundColor.green()).arg(backgroundColor.blue());

    btn->setStyleSheet(style);
}

/* @brief 设置滑动线条的颜色以及按钮点击和悬浮的颜色(是类似相同的)
 * @param color 颜色
 */
void CusButtonGroup::setButtonColor(QColor color)
{
    m_lineColor = color;
}

/* @brief 按钮组中的按钮点击事件
* @param index 按钮组中按钮的id
*/
void CusButtonGroup::onbuttonClicked(int index)
{
    if (m_animation->state() == QPropertyAnimation::Running) {
        m_animation->stop();
    }
    m_btnGroup->button(index)->setChecked(true);
    m_preIndex = m_curIndex;
    m_curIndex = index;
    if (m_btnPosition == CusButtonGroup::North || m_btnPosition == CusButtonGroup::South)
    {
        m_animation->setStartValue(m_offset/*m_preIndex * m_btnSize.width()*/);
        m_animation->setEndValue(index * m_btnSize.width());
    }
    else if (m_btnPosition == CusButtonGroup::West || m_btnPosition == CusButtonGroup::East)
    {
        m_animation->setStartValue(/*m_preIndex * m_btnSize.height()*/m_offset);
        m_animation->setEndValue(index * m_btnSize.height());
    }
    m_animation->start();
}

/* @brief 重置布局
*/
void CusButtonGroup::deleteLayout()
{
    //清除布局，包括布局内控件
    if (this->layout() != nullptr)
    {
        QLayoutItem *child;
        while ((child = this->layout()->takeAt(0)) != 0) {
            delete child->widget();
            delete child;
            child = nullptr;
        }
        m_buttonLst.clear();
        delete this->layout();
        this->setLayout(nullptr);
    }
}

void CusButtonGroup::resizeEvent(QResizeEvent *e)
{
    m_btnSize = m_buttonLst[0]->size();
    QPushButton *thisButton = (QPushButton *)m_btnGroup->button(m_curIndex);
    m_offset = thisButton->x();
}

void CusButtonGroup::setDurnation(int time)
{
    m_animation->setDuration(time);
}
