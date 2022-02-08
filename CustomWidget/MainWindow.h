#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RoundButton.h"
#include "FrameWork.h"
#include "CustomScrollbar.h"
#include "AnimatedCheckBox/AnimatedCheckBox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSharedPointer<RoundButton> mRb;
    std::shared_ptr<FrameWork> mFrameWork;
    std::shared_ptr<CustomScrollbar> mScrollbar;
    std::shared_ptr<CustomScrollbar> mScrollbar1;
    std::shared_ptr<AnimatedCheckBox> mCheckBox;
};
#endif // MAINWINDOW_H
