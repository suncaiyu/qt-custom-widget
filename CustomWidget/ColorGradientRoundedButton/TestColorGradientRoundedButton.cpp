#include "TestColorGradientRoundedButton.h"

TestColorGradientRoundedButton::TestColorGradientRoundedButton(QWidget *parent)
{
    mHLayout = std::make_shared<QHBoxLayout>();
    mVLayout1 = std::make_shared<QVBoxLayout>();
    mVLayout2 = std::make_shared<QVBoxLayout>();
    mHLayout->addLayout(mVLayout1.get());
    mHLayout->addLayout(mVLayout2.get());
    setLayout(mHLayout.get());
    for (int i = 0; i < 8; ++i) {
        auto btn1 = new ColorGradientRoundedButton1;
        btn1->setText(QString("按钮%1").arg(i));
        auto btn2 = new ColorGradientRoundedButton2;
        btn2->setText(QString("按钮%1").arg(i));
        mVLayout1->addWidget(btn1);
        mVLayout2->addWidget(btn2);
        mList1.push_back(btn1);
        mList2.push_back(btn2);
    }
}

TestColorGradientRoundedButton::~TestColorGradientRoundedButton()
{
    for (ColorGradientRoundedButton1 *b : mList1) {
        delete b;
        b = nullptr;
    }

    for (ColorGradientRoundedButton2 *b : mList2) {
        delete b;
        b = nullptr;
    }
}
