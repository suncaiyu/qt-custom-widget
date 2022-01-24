#include "DebugColorDialog.h"
#include "ui_DebugColorDialog.h"
#include <QColorDialog>
#include "Widget.h"
#include <QPainter>
#include <QLinearGradient>

DebugColorDialog::DebugColorDialog(QWidget *parent) :
    FrameWork(parent),
    ui(new Ui::DebugColorDialog)
{
    ui->setupUi(this);
}

DebugColorDialog::~DebugColorDialog()
{
    delete ui;
}

void DebugColorDialog::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    if (mCs1.r == -1 && mCs2.r == -1) {
        return;
    } else if (mCs1.r == -1) {
        p.fillRect(ui->widget->geometry(), mCs2.rgb);
    } else if (mCs2.r == -1) {
        p.fillRect(ui->widget->geometry(), mCs1.rgb);
    } else {
        QLinearGradient lg;
        lg.setStart(0, 0);
        lg.setFinalStop(0, ui->widget->rect().height());
        lg.setColorAt(0, mCs1.rgb);
        lg.setColorAt(1, mCs2.rgb);
        p.fillRect(ui->widget->geometry(), lg);
    }
}

void DebugColorDialog::on_pushButton_clicked()
{
    QColorDialog m_pColorDialog;
    connect(&m_pColorDialog, &QColorDialog::colorSelected, this, [=](const QColor &c){
        mCs1.setValue(c.rgb());
        ui->lineEdit->setText(mCs1.toRGB());
        ui->lineEdit_3->setText(mCs1.toHex1());
    });
    m_pColorDialog.exec();
}

void DebugColorDialog::on_pushButton_2_clicked()
{
    QColorDialog m_pColorDialog;
    connect(&m_pColorDialog, &QColorDialog::colorSelected, this, [=](const QColor &c){
        mCs2.setValue(c.rgb());
        ui->lineEdit_2->setText(mCs2.toRGB());
        ui->lineEdit_4->setText(mCs2.toHex1());
    });
    m_pColorDialog.exec();
}
