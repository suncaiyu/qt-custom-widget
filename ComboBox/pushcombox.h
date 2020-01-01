#ifndef PUSHCOMBOX_H
#define PUSHCOMBOX_H
#include <QPushButton>
#include <QWidget>
#include <QListView>
#include <qstringlistmodel.h>
#include <QModelIndex>
class pushcombox : public QPushButton
{
    Q_OBJECT
public:
    pushcombox(QWidget *widget=0);
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QString currentText READ currentText WRITE setCurrentText NOTIFY currentTextChanged)
    void addtextItem(QString );
    void addtextItems(QStringList);
    int currentIndex(){return  m_currindex;}
    QString currentText(){return m_currenttext;}
    void setCurrentIndex(int i);
    void setCurrentText(QString  str);
signals:
    void    activated(int index);
    void    activated(const QString & text);
    void    currentIndexChanged(int index);
    void    currentTextChanged(const QString text);
public slots:
    void    on_clicked();
    void    on_showPopup();
private:
    QListView *listview;
    QStringListModel *model;
    int m_currindex;
    QString m_currenttext;
    QWidget *listPanel;
    int parentwith;
    int parentheight;
};

#endif // PUSHCOMBOX_H
