#ifndef FLIPGRAPHICSVIEW_H
#define FLIPGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QTimeLine>
class FlipGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    FlipGraphicsView(QWidget *parent = nullptr);
    ~FlipGraphicsView();
    void SetWidgets(QWidget *w1, QWidget *w2);

private:
    QGraphicsProxyWidget *pw1;
    QGraphicsProxyWidget *pw2;
    QScopedPointer<QTimeLine> mTimeline;
    QScopedPointer<QGraphicsScene> mScene;

public slots:
    void StartFlipSlot();
};

#endif // FLIPGRAPHICSVIEW_H
