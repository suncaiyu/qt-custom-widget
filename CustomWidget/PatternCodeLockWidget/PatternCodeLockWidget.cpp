#include "PatternCodeLockWidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

PatternCodeLockWidget::PatternCodeLockWidget(int numberOfEachRowAndCol,QWidget *parent)
    : QWidget(parent),numberOfEachRowAndCol(numberOfEachRowAndCol)
{
    setMouseTracking(true);
    setMinimumSize(400,400);

    for (int i = 0;i < numberOfEachRowAndCol;++i)
    {
        for (int j = 0;j < numberOfEachRowAndCol;++j)
        {
            circularStateList << CircularState::normal;
            smartCircularRectList << QRect();
        }
    }

    connect(&hoverTimer,&QTimer::timeout,this,&PatternCodeLockWidget::onHoverTimer);
    hoverTimer.setInterval(40);
}

PatternCodeLockWidget::~PatternCodeLockWidget()
{
}

void PatternCodeLockWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    const auto rect = event->rect();
    painter.fillRect(rect,QColor("#1D1D1D"));

    auto width = rect.width();
    auto height = rect.height();
    auto sideLength = std::min(width,height) - 20;
    auto halfSideLength = sideLength/2;

    QRect drawZoneRect = QRect(-halfSideLength,-halfSideLength,sideLength,sideLength);
    drawZoneRect.translate(rect.center());

    painter.save();
    painter.setPen(QPen(QBrush("#141414"),5));
    painter.drawRoundedRect(drawZoneRect,12,12);
    painter.restore();

    radiu = sideLength / (1 + 1 + numberOfEachRowAndCol * 2 + (numberOfEachRowAndCol - 1) * 3);

    bool mustUpdateCircularRect = isUpdateSmartCircularRect;
    for (int i = 0,listIndex = 0;i < numberOfEachRowAndCol;++i)
    {
        for (int j = 0;j < numberOfEachRowAndCol;++j,++listIndex)
        {
            QPoint circularCenter = drawZoneRect.topLeft() + QPoint(2*radiu + i*5*radiu,2*radiu + j*5*radiu);
            if(setList.contains(listIndex))
            {
                if(PatternCodeLockSetUpState == PatternCodeLockState::setting ||
                   PatternCodeLockSetUpState == PatternCodeLockState::setted_valid)
                {
                    painter.setPen(QPen(QBrush(QColor("#00FF80")),3));
                }
                else
                {
                    painter.setPen(QPen(QBrush(QColor("#FE4C40")),3));
                }
            }
            else
            {
                painter.setPen(QPen(QBrush(Qt::white),3));
            }

            if(listIndex == lastHoverIndex &&
               hoverTimer.isActive() &&
               PatternCodeLockSetUpState == PatternCodeLockState::setting)
            {
                painter.drawEllipse(circularCenter,radiu + currentchangeLength,radiu + currentchangeLength);
            }
            else
            {
                painter.drawEllipse(circularCenter,radiu,radiu);
            }

            if(mustUpdateCircularRect)
            {
                QRect newCircularRect = QRect(-radiu/2,-radiu/2,radiu,radiu);
                newCircularRect.translate(circularCenter);
                smartCircularRectList[listIndex] = newCircularRect;
            }

            painter.save();
            switch (circularStateList.at(listIndex))
            {
                case CircularState::normal:
                {
                    if(listIndex == lastHoverIndex &&
                       hoverTimer.isActive() &&
                       PatternCodeLockSetUpState == PatternCodeLockState::notSet)
                    {
                        painter.setBrush(Qt::white);
                        painter.setPen(Qt::transparent);
                        painter.drawEllipse(circularCenter,
                                            static_cast<int>(radiu * 0.5 + currentchangeLength),
                                            static_cast<int>(radiu * 0.5 + currentchangeLength));
                    }
                    else
                    {
                        painter.setBrush(QColor("#888888"));
                        painter.setPen(Qt::transparent);
                        painter.drawEllipse(circularCenter,radiu/2,radiu/2);
                    }
                }break;
                case CircularState::hoverOnInnerSamrtCircular:
                {
                    painter.setPen(Qt::transparent);

                    if(PatternCodeLockSetUpState == PatternCodeLockState::notSet)
                    {
                        painter.setBrush(Qt::white);
                        if(hoverTimer.isActive())
                        {
                            painter.drawEllipse(circularCenter,
                                                static_cast<int>(radiu * 0.5 + currentchangeLength),
                                                static_cast<int>(radiu * 0.5 + currentchangeLength));
                        }
                        else
                        {
                            painter.drawEllipse(circularCenter,
                                                static_cast<int>(radiu * 0.7),
                                                static_cast<int>(radiu * 0.7));
                        }
                    }
                    else
                    {
                        if(PatternCodeLockSetUpState == PatternCodeLockState::setting ||
                           PatternCodeLockSetUpState == PatternCodeLockState::setted_valid)
                        {
                            painter.setBrush(QColor("#00FF80"));
                        }
                        else
                        {
                            painter.setBrush(QColor("#FE4C40"));
                        }
                        painter.drawEllipse(circularCenter,
                                            static_cast<int>(radiu * 0.7),
                                            static_cast<int>(radiu * 0.7));
                    }
                }break;
            }
            painter.restore();
        }
    }

    if(PatternCodeLockSetUpState != PatternCodeLockState::notSet)
    {
        painter.setBrush(Qt::transparent);
        if(PatternCodeLockSetUpState == PatternCodeLockState::setted_invalid)
        {
            painter.setPen(QPen(QBrush(QColor("#FE4C40")),7,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        }
        else
        {
            painter.setPen(QPen(QBrush(QColor("#00FF80")),7,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        }
        int setListSize = setList.size();
        for(int i = 0;i < setListSize;++i)
        {
            if(i < (setListSize - 1))
            {
                painter.drawLine(smartCircularRectList.at(setList.at(i)).center(),
                                 smartCircularRectList.at(setList.at(i + 1)).center());
            }
        }

        if(PatternCodeLockSetUpState == PatternCodeLockState::setting)
        {
            painter.drawLine(smartCircularRectList.at(setList.last()).center(),
                             settingMousPos);
        }
    }

    if(mustUpdateCircularRect)
        isUpdateSmartCircularRect = false;
}

void PatternCodeLockWidget::resizeEvent(QResizeEvent *event)
{
    isUpdateSmartCircularRect = true;
    QWidget::resizeEvent(event);
}

void PatternCodeLockWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    int currentHoverIndex = -1;
    if(PatternCodeLockSetUpState == PatternCodeLockState::notSet)
    {
        bool mouseInSomeSmartCircular{false};
        for(int i = 0;i < smartCircularRectList.size();++i)
        {
            if(smartCircularRectList.at(i).contains(pos))
            {
                circularStateList[i] = CircularState::hoverOnInnerSamrtCircular;
                currentHoverIndex = i;
                mouseInSomeSmartCircular = true;
            }
            else
            {
                circularStateList[i] = CircularState::normal;
            }
        }

        if(mouseInSomeSmartCircular)
        {
            lastHoverIndex = currentHoverIndex;
            setCursor(Qt::PointingHandCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }

        if(!hoverTimer.isActive())
        {
            if(this->mouseInSomeSmartCircular != mouseInSomeSmartCircular)//鼠标进入了某个小圆或从小圆出来
            {
                this->mouseInSomeSmartCircular = mouseInSomeSmartCircular;
                if(this->mouseInSomeSmartCircular)
                {
                    currentchangeLength = 0;
                }
                else
                {
                    currentchangeLength = radiu * 0.2;
                }
                hoverTimer.start();
            }
        }
    }
    else if(PatternCodeLockSetUpState == PatternCodeLockState::setting)
    {
        bool mouseInSomeSmartCircular{false};
        for(int i = 0;i < smartCircularRectList.size();++i)
        {
            if(smartCircularRectList.at(i).contains(pos))
            {
                if(!setList.contains(i))
                {
                    setList << i;
                    circularStateList[i] = CircularState::hoverOnInnerSamrtCircular;
                    currentHoverIndex = i;
                }
                mouseInSomeSmartCircular = true;
            }
        }

        if(this->mouseInSomeSmartCircular != mouseInSomeSmartCircular)
        {
            this->mouseInSomeSmartCircular = mouseInSomeSmartCircular;
            if(mouseInSomeSmartCircular)
            {
                lastHoverIndex = currentHoverIndex;
                setCursor(Qt::PointingHandCursor);

                if(!hoverTimer.isActive())
                {
                    currentchangeLength = 0;
                    hoverTimer.start();
                }
            }
            else
            {
                setCursor(Qt::ArrowCursor);
            }
        }

        settingMousPos = pos;
    }
    update();
    QWidget::mouseMoveEvent(event);
}

void PatternCodeLockWidget::onHoverTimer()
{
    if(PatternCodeLockSetUpState == PatternCodeLockState::notSet)
    {
        if(mouseInSomeSmartCircular)
        {
            if(currentchangeLength >= (radiu * 0.2))
            {
                hoverTimer.stop();
            }
            currentchangeLength += 2;
        }
        else
        {
            if(currentchangeLength <= -(radiu * 0.1))
            {
                hoverTimer.stop();
            }
            currentchangeLength -= 2;
        }
    }
    else if(PatternCodeLockSetUpState == PatternCodeLockState::setting)
    {
        if(currentchangeLength >= (radiu * 0.1))
        {
            hoverTimer.stop();
        }
        currentchangeLength += 2;
    }
    update();
}

void PatternCodeLockWidget::mousePressEvent(QMouseEvent *event)
{
    if(lastHoverIndex != -1)
    {
        if(PatternCodeLockSetUpState == PatternCodeLockState::notSet)//开始设置
        {
            PatternCodeLockSetUpState = PatternCodeLockState::setting;
            setList << lastHoverIndex;
            circularStateList[lastHoverIndex] = CircularState::hoverOnInnerSamrtCircular;
            settingMousPos = event->pos();
            currentchangeLength = 0;
            hoverTimer.start();
            update();
        }
    }

    QWidget::mousePressEvent(event);
}

void PatternCodeLockWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(PatternCodeLockSetUpState == PatternCodeLockState::setting && !mouseInSomeSmartCircular)
    {
        if(setList.size() < 4)
        {
            PatternCodeLockSetUpState = PatternCodeLockState::setted_invalid;
            emit setPassword("4位以下的无效密码");
        }
        else
        {
            PatternCodeLockSetUpState = PatternCodeLockState::setted_valid;
            emit setPassword(getPassWord());
        }
        update();
    }

    QWidget::mouseDoubleClickEvent(event);
}

QString PatternCodeLockWidget::getPassWord()
{
    QString psw;
    for(const int & value : setList)
    {
        psw.append(QString::number(value,16));
    }

    return psw;
}

int PatternCodeLockWidget::getNumberOfEachRowAndCol() const
{
    return numberOfEachRowAndCol;
}

void PatternCodeLockWidget::setNumberOfEachRowAndCol(int newNumberOfEachRowAndCol)
{
    if(newNumberOfEachRowAndCol > 1 && newNumberOfEachRowAndCol < 10)
    {
        reset();
        circularStateList.clear();
        smartCircularRectList.clear();
        numberOfEachRowAndCol = newNumberOfEachRowAndCol;
        for (int i = 0;i < numberOfEachRowAndCol;++i)
        {
            for (int j = 0;j < numberOfEachRowAndCol;++j)
            {
                circularStateList << CircularState::normal;
                smartCircularRectList << QRect();
            }
        }
        update();
    }
}

void PatternCodeLockWidget::reset()
{
    PatternCodeLockSetUpState = PatternCodeLockState::notSet;
    std::fill(circularStateList.begin(),circularStateList.end(),CircularState::normal);
    lastHoverIndex = -1;
    hoverTimer.stop();
    currentchangeLength = 0;
    isUpdateSmartCircularRect = true;
    mouseInSomeSmartCircular = false;
    setList.clear();
    settingMousPos = QPoint(0,0);
    update();
}
