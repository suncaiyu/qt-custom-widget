#ifndef TESTCOLORGRADIENTROUNDEDBUTTON_H
#define TESTCOLORGRADIENTROUNDEDBUTTON_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ColorGradientRoundedButton1.h"
#include "ColorGradientRoundedButton2.h"

class TestColorGradientRoundedButton : public QWidget
{
    Q_OBJECT
public:
    TestColorGradientRoundedButton(QWidget *parent = nullptr);
    ~TestColorGradientRoundedButton() override;

private:
    std::shared_ptr<QHBoxLayout> mHLayout;
    std::shared_ptr<QVBoxLayout> mVLayout1;
    std::shared_ptr<QVBoxLayout> mVLayout2;
    std::vector<ColorGradientRoundedButton1 *> mList1;
    std::vector<ColorGradientRoundedButton2 *> mList2;
};

#endif // TESTCOLORGRADIENTROUNDEDBUTTON_H
