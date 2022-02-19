#ifndef FONTAWESOMESHOWFORM_H
#define FONTAWESOMESHOWFORM_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
namespace Ui {
class FontAwesomeShowForm;
}

class ShowWidget : public QWidget {
    Q_OBJECT
public:
    ShowWidget(QWidget *parent = nullptr);
    ~ShowWidget(){};
    void Set(QString s);
    void SetQtIcon(QString s, QPixmap pix);

private:
    std::unique_ptr<QLabel> mName;
    std::unique_ptr<QLabel> mIcon;
    std::unique_ptr<QHBoxLayout> mLayout;
};

class FontAwesomeShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit FontAwesomeShowForm(QWidget *parent = nullptr);
    ~FontAwesomeShowForm();

private:
    Ui::FontAwesomeShowForm *ui;
    std::unique_ptr<QGridLayout> mLayout;

    void Init();
};

#endif // FONTAWESOMESHOWFORM_H
