#include "Widget.h"
#include "ui_Widget.h"
#include <QScreen>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QClipboard>

namespace  {
constexpr int TIME = 50;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    mDebugDialog = QSharedPointer<DebugColorDialog>(new DebugColorDialog(this));
    if (mTimeId == -1) {
        mTimeId = startTimer(TIME);
    }
    mHotkey = QSharedPointer<QHotkey>(new QHotkey(Qt::Key_F, Qt::ShiftModifier | Qt::AltModifier, true, this));
    connect(mHotkey.get(), &QHotkey::activated, this, [=](){
        RestartSlot();
    });
    SetSystemIcon();
}

Widget::~Widget()
{
    if (mTimeId != -1) {
        killTimer(mTimeId);
        mTimeId = -1;
    }
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    DrawPixmap(p);
    QFont font = p.font();
    font.setFamily("华文琥珀");
    font.setPointSizeF(font.pointSizeF() + 5.5);
    p.setFont(font);
    if (mShowText) {
        DrawPosition(p);
        DrawScale(p);
        DrawRGB(p);
        DrawHex(p);
        DrawTip(p);
    }
    if (mShowHelp) {
        DrawHelp(p);
    }
}

void Widget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    mPos = QCursor::pos();
    update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Plus) {
        if (mScale < 50) {
            mScale++;
        }
    }
    if (event->key() == Qt::Key_Minus) {
        if (mScale > 1) {
            mScale--;
        }
    }
    if (event->key() == Qt::Key_F2 && !mShowHelp) {
        mShowText = !mShowText;
    }
    if (event->key() == Qt::Key_C && event->modifiers() == (Qt::ShiftModifier | Qt::AltModifier)) {
        QClipboard *clip  = QApplication::clipboard();
        clip->setText(mCs.toRGB());
    }
    if (event->key() == Qt::Key_V && event->modifiers() == (Qt::ShiftModifier | Qt::AltModifier)) {
        QClipboard *clip  = QApplication::clipboard();
        clip->setText(mCs.toHex());
    }
    if (event->key() == Qt::Key_F1) {
        mShowHelp = true;
        mShowText = false;
    }
    if (event->key() == Qt::Key_Escape && mShowHelp) {
        mShowHelp = false;
        mShowText = true;
    }
    if (event->key() == Qt::Key_F3) {
        if (mDebugDialog->isVisible()) {
            mDebugDialog->close();
        } else {
            mDebugDialog->show();
        }
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void Widget::SetSystemIcon()
{
    mExit = QSharedPointer<QAction>(new QAction(QStringLiteral("退出")));
    connect(mExit.get(), &QAction::triggered, this, [=](){
        qApp->exit(0);
    });
    mMenu = QSharedPointer<QMenu>(new QMenu());
    mMenu->addAction(mExit.get());
    mSystemIcon = QSharedPointer<QSystemTrayIcon>(new QSystemTrayIcon(this));
    mSystemIcon->setToolTip("Color Picker");
    mSystemIcon->setIcon(QIcon(":/xxx.ico"));
    mSystemIcon->setContextMenu(mMenu.get());
    connect(mSystemIcon.get(), &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason){
        switch (reason) {
        case QSystemTrayIcon::Trigger:
            this->RestartSlot();
            break;
        default:
            break;
        }
    });
    mSystemIcon->show();
}

QPixmap Widget::GetPixmap()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pix = screen->grabWindow(0);
    QImage img = pix.toImage();
    QRgb rgb = img.pixel(mPos.x(), mPos.y());
    mCs.setValue(rgb);
    return pix;
}

void Widget::DrawPixmap(QPainter &p)
{
    QPixmap pix = GetPixmap();
    // 换成image后四周边角可以正常draw, pixmap坐标需要计算一下，原因不明白
    QImage pixmap = pix.toImage();
    int distanceX = width() / mScale / 2;
    int distanceY = height() / mScale / 2;
    pixmap = pixmap.copy(mPos.x() - distanceX, mPos.y() - distanceY, width() / mScale,
                         height() / mScale);
    // 取当前鼠标位置窗口大小的图片
    QTransform trans;
    trans.scale(mScale, mScale);
    pixmap = pixmap.transformed(trans);
    p.drawImage(pixmap.rect(), pixmap);
    DrawMark(p, distanceX, distanceY);
}

void Widget::DrawMark(QPainter &p, int distanceX, int distanceY)
{
    QPen pen = p.pen();
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(0.5);
    p.setPen(pen);
    QRect location(distanceX * mScale, distanceY * mScale, 1 * mScale, 1 * mScale);
    p.drawRect(location);
    QPoint top(location.x() + location.width() / 2, location.y());
    p.drawLine(top, top - QPoint(0, 2 * mScale));
    QPoint left(location.x(), location.y() + location.height() / 2);
    p.drawLine(left, left - QPoint(2 * mScale, 0));
    QPoint bottom(location.x() + location.width() / 2, location.y() + location.height());
    p.drawLine(bottom, bottom + QPoint(0, 2 * mScale));
    QPoint right(location.x() + location.width(), location.y() + location.height() / 2);
    p.drawLine(right, right + QPoint(2 * mScale, 0));
}

void Widget::DrawPosition(QPainter &p)
{
    QString pos = "X , Y : " + QString::number(mPos.x()) + " , " + QString::number(mPos.y());
    QFontMetrics fm = p.fontMetrics();
    QRect rc(0, 0, GetSuitableWidth(p, pos), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, pos);
}

void Widget::DrawScale(QPainter &p)
{
    QString scale = "Scale : " + QString::number(mScale) + " * " + QString::number(mScale);
    QFontMetrics fm = p.fontMetrics();
    QRect rc(width() - GetSuitableWidth(p, scale), 0, GetSuitableWidth(p, scale), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, scale);
    scale = "press +/- change";
    rc = QRect(width() - GetSuitableWidth(p, scale), fm.height(), GetSuitableWidth(p, scale), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, scale);
}

void Widget::DrawRGB(QPainter &p)
{
    QString rgb = mCs.toRGB();
    QFontMetrics fm = p.fontMetrics();
    QRect rc(0, fm.height(), GetSuitableWidth(p, rgb), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, rgb);
}

void Widget::DrawHex(QPainter &p)
{
    QString hex = mCs.toHex1();
    QFontMetrics fm = p.fontMetrics();
    QRect rc(0, height() - fm.height(), GetSuitableWidth(p, hex), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, hex);
}

void Widget::DrawTip(QPainter &p)
{
    QString tip = "press F1 for help";
    QFontMetrics fm = p.fontMetrics();
    QRect rc(width() - GetSuitableWidth(p, tip), height() - fm.height(), GetSuitableWidth(p, tip), fm.height());
    p.fillRect(rc, Qt::white);
    p.drawText(rc, tip);
}

void Widget::DrawHelp(QPainter &p)
{
    QString tip1 = "Shift + Alt + F 全局唤醒(其他功能需要选中)";
    QString tip2 = "Shift + Alt + C 复制当前RGB";
    QString tip3 = "Shift + Alt + V 复制当前HEX";
    QString tip4 = "F2 隐藏文字";
    QString tip5 = "ESC 返回";
    QFontMetrics fm = p.fontMetrics();
    QRect rc1(0, 0, GetSuitableWidth(p, tip1), fm.height());
    QRect rc2(0, fm.height(), GetSuitableWidth(p, tip2), fm.height());
    QRect rc3(0, fm.height() * 2, GetSuitableWidth(p, tip3), fm.height());
    QRect rc4(0, fm.height() * 3, GetSuitableWidth(p, tip4), fm.height());
    QRect rc5(0, fm.height() * 4, GetSuitableWidth(p, tip5), fm.height());
    p.fillRect(rc1, Qt::white);
    p.drawText(rc1, tip1);
    p.fillRect(rc2, Qt::white);
    p.drawText(rc2, tip2);
    p.fillRect(rc3, Qt::white);
    p.drawText(rc3, tip3);
    p.fillRect(rc4, Qt::white);
    p.drawText(rc4, tip4);
    p.fillRect(rc5, Qt::white);
    p.drawText(rc5, tip5);
}

int Widget::GetSuitableWidth(QPainter &p, QString str)
{
    QFontMetrics fm = p.fontMetrics();
    return fm.boundingRect(str).width() > fm.horizontalAdvance(str) ? fm.boundingRect(str).width() :
                                                                      fm.horizontalAdvance(str);
}

void Widget::RestartSlot()
{
    if (mTimeId == -1) {
        mTimeId = startTimer(TIME);
    }
    show();
    activateWindow();
}

