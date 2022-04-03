#ifndef IRREGULARPOPUPWIDGET_H
#define IRREGULARPOPUPWIDGET_H

#include <QWidget>

class IrregularPopupWidget : public QWidget
{
    Q_OBJECT

public:
    IrregularPopupWidget(QWidget *parent = nullptr);
    ~IrregularPopupWidget()override;

    void setText(const QString &newText);
    enum class SharpCornersPosition
    {
        left = 0,
        right,
        top,
        bottom
    };
    void setWidgetSharpCornersPosition(SharpCornersPosition newWidgetSharpCornersPosition);

protected:
    void paintEvent(QPaintEvent *event)override;
    QSize sizeHint() const override;

private:
    SharpCornersPosition widgetSharpCornersPosition{SharpCornersPosition::left};
    int SharpCornersRectWidth{30};
    int SharpCornersRectHeight{30};
    QColor backgroundColor{"#31305a"};
    QString text;
};
#endif // IRREGULARPOPUPWIDGET_H
