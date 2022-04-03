#ifndef TESTPATTERNCODELOCKWIDGET_H
#define TESTPATTERNCODELOCKWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include "PatternCodeLockWidget.h"

class TestPatternCodeLockWidget : public QWidget
{
    Q_OBJECT
public:
    TestPatternCodeLockWidget(QWidget *parent = nullptr);
    ~TestPatternCodeLockWidget();

private:
    std::shared_ptr<QVBoxLayout> mVLayout;
    std::shared_ptr<QHBoxLayout> mHLayout;
    std::shared_ptr<PatternCodeLockWidget> mlockWidget;
    std::shared_ptr<QPushButton> mButton;
    std::shared_ptr<QSpinBox> mSpinBox;
    std::shared_ptr<QLabel> mLabel1;
    std::shared_ptr<QLabel> mLabel2;
    std::shared_ptr<QLineEdit> mEdit;
};

#endif // TESTPATTERNCODELOCKWIDGET_H
