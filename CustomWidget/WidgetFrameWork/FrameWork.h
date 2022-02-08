#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <QWidget>
#include <QCloseEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class FrameWork : public QWidget
{
    Q_OBJECT
public:
    explicit FrameWork(QWidget *parent = nullptr);
    virtual ~FrameWork();
protected:
    void closeEvent(QCloseEvent *e) override;
    void showEvent(QShowEvent *event) override;
signals:

private:
    QSharedPointer<QParallelAnimationGroup> amiGroup;
    QSharedPointer<QPropertyAnimation> ami1;
    QSharedPointer<QPropertyAnimation> ami2;
    QWidget *mParent;
    QSize mShowSize;
};

#endif // FRAMEWORK_H
