#ifndef FONTAWESOMEHELPER_H
#define FONTAWESOMEHELPER_H
#include <QFont>
#include <QMap>
#include <QColor>
#include <QDebug>
#include "FontAwesomeShowForm.h"

class FontAwesomeHelper
{
public:
    static FontAwesomeHelper *GetInstance();
    // 不用指针
//    static FontAwesomeHelper &Instance();
    void SetIcon(QWidget *widget, const QString &iconName, int iconSize, const QColor &color = QColor());
    QChar IconUnicode(const QString &iconName);
    QFont GetAwesomeFont() { return mFont; };
    QMap<QString, QString> mIconUnicodeMap;
    void ShowHelper();

private:
    FontAwesomeHelper();
    FontAwesomeHelper(const FontAwesomeHelper &) = delete;
    FontAwesomeHelper &operator=(const FontAwesomeHelper &) = delete;
    static FontAwesomeHelper *mInstance;
    QFont mFont;
    std::shared_ptr<FontAwesomeShowForm> mShowFontAswsome;

    class CGarbo
    {
    public:
        ~CGarbo() {
            if (FontAwesomeHelper::mInstance)
            {
                qDebug() << "delete";
                delete FontAwesomeHelper::mInstance;
                FontAwesomeHelper::mInstance = nullptr;
            }
        }
    };
    // 1
//    static CGarbo Garbo;
};

#endif // FONTAWESOMEHELPER_H
