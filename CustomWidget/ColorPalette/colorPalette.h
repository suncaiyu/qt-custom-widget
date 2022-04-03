#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QWidget>

class colorPalette : public QWidget
{
    Q_OBJECT
public:
    explicit colorPalette(QWidget *parent = nullptr);

signals:
    void colorString(QString);
protected:
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private:
    bool isPointInCir(const QPoint &point,const QRect & rect);//判断点是否在圆范围内
    QPoint pressPos;
    int radius;
    QRect boundingRect;
};

#endif // COLORPALETTE_H
