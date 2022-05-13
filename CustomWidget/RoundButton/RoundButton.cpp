#include "RoundButton.h"
#include <QPainter>
#include <QDebug>

RoundButton::RoundButton(QWidget *parent) : QPushButton(parent)
{
    //设置具体阴影
    mShadow = std::make_shared<QGraphicsDropShadowEffect>(this);
    mShadow->setOffset(0, 0);
    //阴影颜色
    mShadow->setColor(QColor(38, 78, 119, 127));
    //阴影半径
    mShadow->setBlurRadius(22);
    setGraphicsEffect(mShadow.get());
    initStyleOption(&mOption);
    mOriginColor = mBackColor = QColor(97,194,207);
    mLighterColor = mOriginColor.lighter(130);
}

RoundButton::RoundButton(QString str, QWidget *parent) : RoundButton(parent)
{
    setText(str);
}

RoundButton::~RoundButton(){}

void RoundButton::setText(const QString &text)
{
    mOption.text = text;
    QPushButton::setText(text);
}

void RoundButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QLinearGradient lg;
    lg.setFinalStop(0, rect().height());
    lg.setStart(0, 0);
    lg.setColorAt(0, mBackColor);
    lg.setColorAt(1, mBackColor.darker(140));
    p.setRenderHint(QPainter::Antialiasing);
    p.save();
    p.setPen(Qt::NoPen);
    p.setBrush(lg);
    p.drawRoundedRect(rect(), rect().height() / 2, rect().height() / 2);
    p.restore();
    QPen pen = p.pen();
    pen.setColor(Qt::white);
    p.setPen(pen);
    QFont font = p.font();
    font.setFamily("华文琥珀");
    if (mOption.state.testFlag(QStyle::State_Selected)) {
        font.setItalic(true);
    }
    if (mOption.state.testFlag(QStyle::State_MouseOver)) {
        font.setUnderline(2);
    }
    p.setFont(font);
    p.drawText(rect(), Qt::AlignCenter, mOption.text);
}

void RoundButton::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    mOption.state.operator|=(QStyle::State_Selected);
    update();
}

void RoundButton::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    mOption.state.operator^=(QStyle::State_Selected);
    update();
}
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
void RoundButton::enterEvent(QEnterEvent *e)
{
    QPushButton::enterEvent(e);
    mBackColor = mLighterColor;
    mOption.state.operator|=(QStyle::State_MouseOver);
    update();
}
#else
void RoundButton::enterEvent(QEvent *e)
{
    QPushButton::enterEvent(e);
    mBackColor = mLighterColor;
    mOption.state.operator|=(QStyle::State_MouseOver);
    update();
}
#endif

void RoundButton::leaveEvent(QEvent *e)
{
    QPushButton::leaveEvent(e);
    mBackColor = mOriginColor;
    mOption.state.operator^=(QStyle::State_MouseOver);
    update();
}
