//wating.h
#ifndef WATING_H
#define WATING_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
namespace Ui {
class Waiting;
}

class wating : public QWidget
{
    Q_OBJECT

public:
    explicit wating(QWidget *parent = 0);
    ~wating();

protected:
    void paintEvent(QPaintEvent *event);

public slots:


signals:
    void loading();

private:
    Ui::Waiting *ui;
    QMovie *movie;
    QLabel *label;
    QLabel * tip_label;
    QFrame * background;
    QTimer *timer ;
};

#endif // WATING_H
