#ifndef HOVERWIDGET_H
#define HOVERWIDGET_H
#include <QWidget>
#include <QGraphicsDropShadowEffect>

class HoverWidget : public QWidget
{
    Q_OBJECT
public:
    HoverWidget(QWidget *parent = 0);
    ~HoverWidget();
    int GetOffset() {return mOffset;}
    int GetBlurRadius(){return mBlurRadius;}
    int GetRadius() {return mRadius;}
    QRect GetContentRect() {return mContentRect;}
    void SetFlat(bool f) {mFlat = f;}
    bool GetFlat() {return mFlat;}

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int mMargin = 15;
    int mBlurRadius = 15;
    int mOffset = 5;
    int mRadius = 15;
    QRect mContentRect;
    QSharedPointer<QGraphicsDropShadowEffect> mEffect;
    bool mFlat = true;
    QString mText;
};

#endif // HOVERWIDGET_H
