#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QWidget>


namespace Ui {
class CustomMenu;
}

class CustomMenu : public QWidget
{
    Q_OBJECT

public:
    explicit CustomMenu(QWidget *parent = nullptr);
    ~CustomMenu();

protected:
    void mousePressEvent(QMouseEvent *e);
private:
    Ui::CustomMenu *ui;
};

#endif // CUSTOMMENU_H
