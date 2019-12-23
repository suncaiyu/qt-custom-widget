#ifndef CHARTPANEL_H
#define CHARTPANEL_H

#include <QWidget>

namespace Ui {
class ChartPanel;
}

class ChartPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ChartPanel(QWidget *parent = 0);
    ~ChartPanel();
    void paintEvent(QPaintEvent *event);
    void chartAppendPoint(float x,float y);
private:
    Ui::ChartPanel *ui;
    int count;
    QList<float> xList;
    QList<float> yList;
};

#endif // CHARTPANEL_H
