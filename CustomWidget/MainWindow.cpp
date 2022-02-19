#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mRb = QSharedPointer<RoundButton>(new RoundButton("好文要顶", this));
    mRb->resize(100, 50);
    mRb->move(100, 100);
    mFrameWork = std::make_shared<FrameWork>(this);
    connect(mRb.get(), &RoundButton::clicked, this, [=](){
        qDebug() << "test";
        if (mFrameWork->isVisible()) {
            mFrameWork->close();
        } else {
            mFrameWork->show();
        }
    });
    mScrollbar = std::make_shared<CustomScrollbar>();
    mScrollbar1 = std::make_shared<CustomScrollbar>(Qt::Orientation::Vertical);
    ui->verticalLayout_3->addWidget(mScrollbar.get());
    ui->horizontalLayout_4->addWidget(mScrollbar1.get());
    connect(mScrollbar.get(), &CustomScrollbar::ValueChangeSignal, this, [this](qreal v){
        ui->lineEdit->setText(QString::number(v));
    });
    connect(ui->lineEdit, &QLineEdit::textChanged, this, [this](const QString &p){
        mScrollbar1->SetValue(p.toDouble());
    });
    mCheckBox = std::make_shared<AnimatedCheckBox>(this);
    mCheckBox->resize(100, 50);
    mCheckBox->move(200, 100);
    TestFlipGraphicsView();
    TestFlip();
    FontAwesomeHelper::GetInstance()->ShowHelper();
    mRouletteWidget = std::make_shared<RouletteSelectWidget>(this);
    mRouletteWidget->resize(300, 300);
    mRouletteWidget->SetLayerAndCount(2, QList<int>() << 3 << 4);
    mRouletteWidget->move(0, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestFlipGraphicsView()
{
    mView = std::make_shared<FlipGraphicsView>();
    mFrameLayout = std::make_shared<QVBoxLayout>();
    mFrameWork->setLayout(mFrameLayout.get());
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
}

void MainWindow::TestFlip()
{
    mFlipWidget = std::make_shared<FlipWidget>();
    mFrameWork->layout()->addWidget(mFlipWidget.get());
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
}
