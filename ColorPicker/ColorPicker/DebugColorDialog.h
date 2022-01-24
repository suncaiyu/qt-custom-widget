#ifndef DEBUGCOLORDIALOG_H
#define DEBUGCOLORDIALOG_H

#include <QWidget>
#include <FrameWork.h>
#include "utils.h"
namespace Ui {
class DebugColorDialog;
}

class DebugColorDialog : public FrameWork
{
    Q_OBJECT
public:
    explicit DebugColorDialog(QWidget *parent = nullptr);
    ~DebugColorDialog();

protected:
    void paintEvent(QPaintEvent *e) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

 private:
    Ui::DebugColorDialog *ui;
    ColorString mCs1;
    ColorString mCs2;
};

#endif // DEBUGCOLORDIALOG_H
