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
#include "PictureShow/ShowPicture.h"
#include "FlowLayout/FlowLayout.h"
#include "RoundMmenuInUpperLeftCornerWidget/RoundMmenuInUpperLeftCornerWidget.h"
#include "PatternCodeLockWidget/TestPatternCodeLockWidget.h"
#include "IrregularPopupWidget/TestIrregularPopupWidget.h"
#include "ColorGradientRoundedButton/TestColorGradientRoundedButton.h"
#include "DragSliderVerify/DragSliderVerify.h"
#include "PlayStateControl/PlayStateControl.h"
#include "ColorfulSlidingRing/ColorfulSlidingRing.h"
#include "DiscButton/DiscButton.h"
#include "ColorPalette/colorPalette.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();

private slots:

private:
    Ui::MainWindow *ui;
    std::shared_ptr<FlowLayout> mFlowLayout;
    std::shared_ptr<RoundButton> mFuncButton1;
    std::shared_ptr<FrameWork> mFrameWork1;
    std::shared_ptr<FlipGraphicsView> mView;
    std::shared_ptr<FlipWidget> mFlipWidget;
    std::shared_ptr<QVBoxLayout> mFrameLayout;

    QSharedPointer<RoundButton> mFuncButton2;
    std::shared_ptr<FrameWork> mFrameWork2;
    std::shared_ptr<AnimatedCheckBox> mCheckBox;

    std::shared_ptr<RoundButton> mFuncButton3;
    std::shared_ptr<FrameWork> mFrameWork3;
    std::shared_ptr<CustomScrollbar> mScrollbar;
    std::shared_ptr<CustomScrollbar> mScrollbar1;

    std::shared_ptr<RoundButton> mFuncButton4;
    std::shared_ptr<FrameWork> mFrameWork4;
    std::shared_ptr<RouletteSelectWidget> mRouletteWidget;

    std::shared_ptr<RoundButton> mFuncButton5;

    std::shared_ptr<RoundButton> mFuncButton6;
    std::shared_ptr<ShowPicture> mQuickWidget;

    std::shared_ptr<RoundButton> mFuncButton7;
    std::shared_ptr<FrameWork> mFrameWork7;
    std::shared_ptr<RoundMmenuInUpperLeftCornerWidget> mRoundMenu;

    std::shared_ptr<RoundButton> mFuncButton8;
    std::shared_ptr<TestPatternCodeLockWidget> mShowWidget8;

    std::shared_ptr<RoundButton> mFuncButton9;
    std::shared_ptr<TestIrregularPopupWidget> mShowWidget9;

    std::shared_ptr<RoundButton> mFuncButton10;
    std::shared_ptr<TestColorGradientRoundedButton> mShowWidget10;

    std::shared_ptr<RoundButton> mFuncButton11;
    std::shared_ptr<DragSliderVerify> mShowWidget11;

    std::shared_ptr<RoundButton> mFuncButton12;
    std::shared_ptr<PlayStateControl> mShowWidget12;

    std::shared_ptr<RoundButton> mFuncButton13;
    std::shared_ptr<ColorfulSlidingRing> mShowWidget13;

    std::shared_ptr<RoundButton> mFuncButton14;
    std::shared_ptr<DiscButton> mShowWidget14;

    std::shared_ptr<RoundButton> mFuncButton15;
    std::shared_ptr<colorPalette> mShowWidget15;

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

    void InitFlowLayout();
    void InitFunc1();
    void InitFunc2();
    void InitFunc3();
    void InitFunc4();
    void InitFunc5();
    void InitFunc6();
    void InitFunc7();
    void InitFunc8();
    void InitFunc9();
    void InitFunc10();
    void InitFunc11();
    void InitFunc12();
    void InitFunc13();
    void InitFunc14();
    void InitFunc15();
};
#endif // MAINWINDOW_H
