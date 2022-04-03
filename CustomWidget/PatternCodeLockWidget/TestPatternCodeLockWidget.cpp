#include "TestPatternCodeLockWidget.h"

TestPatternCodeLockWidget::TestPatternCodeLockWidget(QWidget *parent)
{
    mlockWidget = std::make_shared<PatternCodeLockWidget>(3);

    mSpinBox = std::make_shared<QSpinBox>();
    mSpinBox->setRange(2, 8);
    mSpinBox->setMinimumWidth(100);
    mSpinBox->setValue(mlockWidget->getNumberOfEachRowAndCol());

    mHLayout = std::make_shared<QHBoxLayout>();
    mVLayout = std::make_shared<QVBoxLayout>();

    mLabel1 = std::make_shared<QLabel>("设置的密码：");
    mButton = std::make_shared<QPushButton>("还原");
    mLabel2 = std::make_shared<QLabel>("设置行列数：");
    mEdit = std::make_shared<QLineEdit>();

    mHLayout->addWidget(mLabel1.get());
    mHLayout->addWidget(mEdit.get());
    mHLayout->addWidget(mLabel2.get());
    mHLayout->addWidget(mSpinBox.get());
    mHLayout->addWidget(mButton.get());

    mVLayout->addWidget(mlockWidget.get(), 5);
    mVLayout->addLayout(mHLayout.get(), 1);
    setLayout(mVLayout.get());

    QObject::connect(mlockWidget.get(), &PatternCodeLockWidget::setPassword, mEdit.get(), &QLineEdit::setText);
    QObject::connect(mSpinBox.get(), static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), mlockWidget.get(), &PatternCodeLockWidget::setNumberOfEachRowAndCol);
    QObject::connect(mButton.get(), &QPushButton::clicked, mlockWidget.get(), &PatternCodeLockWidget::reset);
}

TestPatternCodeLockWidget::~TestPatternCodeLockWidget()
{

}
