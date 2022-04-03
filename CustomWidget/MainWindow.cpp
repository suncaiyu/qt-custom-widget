#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <ColorManager/ColorManager.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    QColor c(186, 43, 188);
    qDebug() << ColorManager::IsDarkColor(c);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    InitFlowLayout();
    InitFunc1();
    InitFunc2();
    InitFunc3();
    InitFunc4();
    InitFunc5();
    InitFunc6();
    InitFunc7();
    InitFunc8();
    InitFunc9();
    InitFunc10();
    InitFunc11();
    InitFunc12();
    InitFunc13();
    InitFunc14();
    InitFunc15();
}

void MainWindow::InitFlowLayout()
{
    mFlowLayout = std::make_shared<FlowLayout>(ui->centralwidget, 10, 10, 10);
    ui->centralwidget->setLayout(mFlowLayout.get());
}

void MainWindow::InitFunc1()
{
    mFuncButton1 = std::make_shared<RoundButton>("FlipWidget");
    mFlowLayout->addWidget(mFuncButton1.get());
    mFrameWork1 = std::make_shared<FrameWork>(this);
    auto InitFlipGraphicsView = [this](){
        mView = std::make_shared<FlipGraphicsView>();
        mFrameLayout = std::make_shared<QVBoxLayout>();
        mFrameWork1->setLayout(mFrameLayout.get());
        mFrameLayout->addWidget(mView.get());

        s1.w1 = std::make_shared<QWidget>();
        s1.w2 = std::make_shared<QWidget>();
        s1.l1 = std::make_shared<QVBoxLayout>();
        s1.l2 = std::make_shared<QVBoxLayout>();
        s1.b1 = std::make_shared<QPushButton>(" this is button 1 ");
        s1.b2 = std::make_shared<QPushButton>(" this is button 2 ");
        connect(s1.b1.get(), SIGNAL(clicked()), mView.get(), SLOT(StartFlipSlot()));
        connect(s1.b2.get(), &QPushButton::clicked, mView.get(), &FlipGraphicsView::StartFlipSlot);
        s1.l1->addWidget(s1.b1.get());
        s1.w1->setLayout(s1.l1.get());
        s1.l2->addWidget(s1.b2.get());
        s1.w2->setLayout(s1.l2.get());
        mView->SetWidgets(s1.w1.get(), s1.w2.get());
    };

    auto InitFlipWidget = [this](){
        mFlipWidget = std::make_shared<FlipWidget>();
        mFrameWork1->layout()->addWidget(mFlipWidget.get());
        s2.w1 = std::make_shared<QWidget>();
        s2.w2 = std::make_shared<QWidget>();
        s2.l1 = std::make_shared<QVBoxLayout>();
        s2.l2 = std::make_shared<QVBoxLayout>();
        s2.b1 = std::make_shared<QPushButton>(" this is button 1 ");
        s2.b2 = std::make_shared<QPushButton>(" this is button 2 ");
        connect(s2.b1.get(), SIGNAL(clicked()), mFlipWidget.get(), SLOT(StartFlip()));
        connect(s2.b2.get(), &QPushButton::clicked, mFlipWidget.get(), &FlipWidget::StartFlip);
        s2.l1->addWidget(s2.b1.get());
        s2.w1->setLayout(s2.l1.get());
        s2.l2->addWidget(s2.b2.get());
        s2.w2->setLayout(s2.l2.get());
        mFlipWidget->SetWidgets(s2.w1.get(), s2.w2.get());
    };

    InitFlipGraphicsView();
    InitFlipWidget();
    connect(mFuncButton1.get(), &RoundButton::clicked, this, [=](){
        if (mFrameWork1->isVisible()) {
            mFrameWork1->close();
        } else {
            mFrameWork1->show();
        }
    });
}

void MainWindow::InitFunc2()
{
    mFuncButton2 = QSharedPointer<RoundButton>(new RoundButton("CheckBox", this));
    mFlowLayout->addWidget(mFuncButton2.get());
    mFrameWork2 = std::make_shared<FrameWork>(this);
    mCheckBox = std::make_shared<AnimatedCheckBox>(mFrameWork2.get());
    connect(mFuncButton2.get(), &RoundButton::clicked, this, [=](){
        if (mFrameWork2->isVisible()) {
            mFrameWork2->close();
        } else {
            mFrameWork2->show();
        }
    });
}

void MainWindow::InitFunc3()
{
    mFuncButton3 = std::make_shared<RoundButton>("Scrollbar", this);
    mFlowLayout->addWidget(mFuncButton3.get());
    mFrameWork3 = std::make_shared<FrameWork>(this);
    connect(mFuncButton3.get(), &RoundButton::clicked, this, [=](){
        if (mFrameWork3->isVisible()) {
            mFrameWork3->close();
        } else {
            mFrameWork3->show();
        }
    });
    mScrollbar = std::make_shared<CustomScrollbar>(Qt::Orientation::Horizontal, (QWidget *)mFrameWork3.get());
    mScrollbar1 = std::make_shared<CustomScrollbar>(Qt::Orientation::Vertical, (QWidget *)mFrameWork3.get());
    mScrollbar->setGeometry(0, 0, 200, 25);
    mScrollbar1->setGeometry(0, 25, 25, 200);
}

void MainWindow::InitFunc4()
{
    mFuncButton4 = std::make_shared<RoundButton>("RouletteWidget", this);
    mFlowLayout->addWidget(mFuncButton4.get());
    mFrameWork4 = std::make_shared<FrameWork>(this);
    connect(mFuncButton4.get(), &RoundButton::clicked, this, [=](){
        if (mFrameWork4->isVisible()) {
            mFrameWork4->close();
        } else {
            mFrameWork4->show();
        }
    });
    mRouletteWidget = std::make_shared<RouletteSelectWidget>(mFrameWork4.get());
    mRouletteWidget->resize(300, 300);
    mRouletteWidget->SetLayerAndCount(2, QList<int>() << 3 << 4);
    mRouletteWidget->move(0, 0);
}

void MainWindow::InitFunc5()
{
    mFuncButton5 = std::make_shared<RoundButton>("FontAwesome Icon", this);
    mFlowLayout->addWidget(mFuncButton5.get());
    connect(mFuncButton5.get(), &RoundButton::clicked, this, [=](){
        FontAwesomeHelper::GetInstance()->ShowHelper();
    });
}

void MainWindow::InitFunc6()
{
    mFuncButton6 = std::make_shared<RoundButton>("Show Picture", this);
    mFlowLayout->addWidget(mFuncButton6.get());
    mQuickWidget = std::make_shared<ShowPicture>();
    connect(mFuncButton6.get(), &RoundButton::clicked, this, [=](){
        if (mQuickWidget->isVisible()) {
            mQuickWidget->close();
        } else {
            mQuickWidget->show();
        }
    });
}

void MainWindow::InitFunc7()
{
    mFuncButton7 = std::make_shared<RoundButton>("Round Menu", this);
    mFlowLayout->addWidget(mFuncButton7.get());
    mFrameWork7 = std::make_shared<FrameWork>(this);
    connect(mFuncButton7.get(), &RoundButton::clicked, this, [=](){
        if (mFrameWork7->isVisible()) {
            mFrameWork7->close();
        } else {
            mFrameWork7->show();
        }
    });
    mRoundMenu = std::make_shared<RoundMmenuInUpperLeftCornerWidget>(mFrameWork7.get());
    mRoundMenu->resize(300, 300);
}

void MainWindow::InitFunc8()
{
    mFuncButton8 = std::make_shared<RoundButton>("Pattern Code Lock", this);
    mFlowLayout->addWidget(mFuncButton8.get());
    mShowWidget8 = std::make_shared<TestPatternCodeLockWidget>();
    connect(mFuncButton8.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget8->isVisible()) {
            mShowWidget8->close();
        } else {
            mShowWidget8->show();
        }
    });
}

void MainWindow::InitFunc9()
{
    mFuncButton9 = std::make_shared<RoundButton>("Irregular Popup", this);
    mFlowLayout->addWidget(mFuncButton9.get());
    mShowWidget9 = std::make_shared<TestIrregularPopupWidget>();
    connect(mFuncButton9.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget9->isVisible()) {
            mShowWidget9->close();
        } else {
            mShowWidget9->show();
        }
    });
}

void MainWindow::InitFunc10()
{
    mFuncButton10 = std::make_shared<RoundButton>("ColorGradient Button", this);
    mFlowLayout->addWidget(mFuncButton10.get());
    mShowWidget10 = std::make_shared<TestColorGradientRoundedButton>();
    connect(mFuncButton10.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget10->isVisible()) {
            mShowWidget10->close();
        } else {
            mShowWidget10->show();
        }
    });
}

void MainWindow::InitFunc11()
{
    mFuncButton11 = std::make_shared<RoundButton>("Drag Slider Verify", this);
    mFlowLayout->addWidget(mFuncButton11.get());
    mShowWidget11 = std::make_shared<DragSliderVerify>();
    connect(mFuncButton11.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget11->isVisible()) {
            mShowWidget11->close();
        } else {
            mShowWidget11->show();
        }
    });
}

void MainWindow::InitFunc12()
{
    mFuncButton12 = std::make_shared<RoundButton>("Play State Control", this);
    mFlowLayout->addWidget(mFuncButton12.get());
    mShowWidget12 = std::make_shared<PlayStateControl>();
    connect(mFuncButton12.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget12->isVisible()) {
            mShowWidget12->close();
        } else {
            mShowWidget12->show();
        }
    });
}

void MainWindow::InitFunc13()
{
    mFuncButton13 = std::make_shared<RoundButton>("Play State Control", this);
    mFlowLayout->addWidget(mFuncButton13.get());
    mShowWidget13 = std::make_shared<ColorfulSlidingRing>();
    connect(mFuncButton13.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget13->isVisible()) {
            mShowWidget13->close();
        } else {
            mShowWidget13->show();
        }
    });
}

void MainWindow::InitFunc14()
{
    mFuncButton14 = std::make_shared<RoundButton>("Disc Button", this);
    mFlowLayout->addWidget(mFuncButton14.get());
    mShowWidget14 = std::make_shared<DiscButton>();
    connect(mFuncButton14.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget14->isVisible()) {
            mShowWidget14->close();
        } else {
            mShowWidget14->show();
        }
    });
}

void MainWindow::InitFunc15()
{
    mFuncButton15 = std::make_shared<RoundButton>("Color Palette", this);
    mFlowLayout->addWidget(mFuncButton15.get());
    mShowWidget15 = std::make_shared<colorPalette>();
    connect(mFuncButton15.get(), &RoundButton::clicked, this, [=](){
        if (mShowWidget15->isVisible()) {
            mShowWidget15->close();
        } else {
            mShowWidget15->show();
        }
    });
}
