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
}

MainWindow::~MainWindow()
{
    delete ui;
}

