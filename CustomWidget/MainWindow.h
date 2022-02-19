#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RoundButton.h"
#include "FrameWork.h"
#include "CustomScrollbar.h"
#include "AnimatedCheckBox/AnimatedCheckBox.h"
#include "FlipGraphicsView.h"
#include "FlipWidget/FlipWidget.h"
#include "FontAwesomeShowForm.h"
#include "RouletteSelectWidget.h"
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    QSharedPointer<RoundButton> mRb;
    std::shared_ptr<FrameWork> mFrameWork;
    std::shared_ptr<CustomScrollbar> mScrollbar;
    std::shared_ptr<CustomScrollbar> mScrollbar1;
    std::shared_ptr<AnimatedCheckBox> mCheckBox;
    std::shared_ptr<FlipGraphicsView> mView;
    std::shared_ptr<FlipWidget> mFlipWidget;
    std::shared_ptr<QVBoxLayout> mFrameLayout;
    std::shared_ptr<RouletteSelectWidget> mRouletteWidget;

    void TestFlipGraphicsView();
    void TestFlip();
    struct SimpleWidget {
        std::shared_ptr<QWidget> w1;
        std::shared_ptr<QWidget> w2;
        std::shared_ptr<QVBoxLayout> l1;
        std::shared_ptr<QVBoxLayout> l2;
        std::shared_ptr<QPushButton> b1;
        std::shared_ptr<QPushButton> b2;
    };
    SimpleWidget s1;
    SimpleWidget s2;
};
#endif // MAINWINDOW_H
