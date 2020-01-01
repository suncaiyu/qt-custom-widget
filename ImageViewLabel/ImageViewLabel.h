#ifndef IMAGEVIEWLABEL_H
#define IMAGEVIEWLABEL_H
#include <QWidget>
#include <QLabel>

class QButtonGroup;
class QPropertyAnimation;
class QParallelAnimationGroup;
class QHBoxLayout;
class ImageViewLabel : public QLabel
{
    Q_OBJECT
public:
    ImageViewLabel(QWidget *parent);
    ~ImageViewLabel();
    void addImage(const QList<std::pair<QString, QString>> &imagepathpairlst);

private slots:
    void onImagevalueChanged(const QVariant &variant);
    void onBtnExpvalueChanged(const QVariant &variant);
    void onBtnShrikvalueChanged(const QVariant &variant);
    void onbuttonClicked(int index);
    void onImageShowTimeOut();

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    int m_offset;
    int m_curIndex;
    int m_preIndex;
    bool m_blefttoright;
    QButtonGroup *m_btnGroup;
    QParallelAnimationGroup *m_btnParalGroup;
    QPropertyAnimation *m_imageAnimation;
    QPropertyAnimation *m_btnExpAnimation;
    QPropertyAnimation *m_btnShrikAnimation;
    QWidget *m_horizontalLayoutWidget;
    QHBoxLayout *m_switchBtnLayout;
    QTimer *m_imageTimer;
    QList<std::pair<QString, QString>> m_imagepathpairlst;
    void initControl();
};

#endif // IMAGEVIEWLABEL_H
