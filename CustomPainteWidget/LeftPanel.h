#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QFrame>

namespace Ui {
class LeftPanel;
}

class LeftPanel : public QFrame
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = nullptr);
    ~LeftPanel();
protected:
    void paintEvent(QPaintEvent *) override;
private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::LeftPanel *ui;
};

#endif // LEFTPANEL_H
