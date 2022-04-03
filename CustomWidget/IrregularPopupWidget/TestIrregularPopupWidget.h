#ifndef TESTIRREGULARPOPUPWIDGET_H
#define TESTIRREGULARPOPUPWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "IrregularPopupWidget.h"

class TestIrregularPopupWidget : public QWidget
{
    Q_OBJECT
public:
    TestIrregularPopupWidget(QWidget *parent = nullptr);
    ~TestIrregularPopupWidget();

private:
    std::shared_ptr<QVBoxLayout> mLayout;
    std::shared_ptr<IrregularPopupWidget> mWidget;
    std::shared_ptr<QPushButton> mButton;
    static int ppp;
};

#endif // TESTIRREGULARPOPUPWIDGET_H
