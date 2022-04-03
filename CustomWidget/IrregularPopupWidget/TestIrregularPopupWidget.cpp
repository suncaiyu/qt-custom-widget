#include "TestIrregularPopupWidget.h"
int TestIrregularPopupWidget::ppp = 0;
TestIrregularPopupWidget::TestIrregularPopupWidget(QWidget *parent)
{
    mLayout = std::make_shared<QVBoxLayout>();
    mButton = std::make_shared<QPushButton>("Change");
    mWidget = std::make_shared<IrregularPopupWidget>();
    mWidget->setText("This is a test demo!!!");
//    mWidget->setWidgetSharpCornersPosition(IrregularPopupWidget::SharpCornersPosition::top);
    mLayout->addWidget(mWidget.get());
    mLayout->addWidget(mButton.get());
    setLayout(mLayout.get());
    connect(mButton.get(), &QPushButton::clicked, this, [this](){
        switch (this->ppp) {
            case 0: {
                mWidget->setWidgetSharpCornersPosition(IrregularPopupWidget::SharpCornersPosition::top);
                break;
            }
            case 1:{
                mWidget->setWidgetSharpCornersPosition(IrregularPopupWidget::SharpCornersPosition::right);
                break;
            }
            case 2 :{
                mWidget->setWidgetSharpCornersPosition(IrregularPopupWidget::SharpCornersPosition::bottom);
                break;
            }
            case 3:{
                mWidget->setWidgetSharpCornersPosition(IrregularPopupWidget::SharpCornersPosition::left);
                break;
            }
            default:{
                break;
            }
        }
        this->ppp++;
        if (this->ppp > 3) {
            this->ppp = 0;
        }
    });
}

TestIrregularPopupWidget::~TestIrregularPopupWidget()
{

}
