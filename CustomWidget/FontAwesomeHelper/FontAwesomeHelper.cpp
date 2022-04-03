#include "FontAwesomeHelper.h"
#include <QMutex>
#include <QFontDatabase>
#include <QFileInfo>
#include <QFile>
#include <QWidget>
#include <QLabel>
#include <QAbstractButton>

FontAwesomeHelper *FontAwesomeHelper::mInstance = nullptr;
// 1
//FontAwesomeHelper::CGarbo FontAwesomeHelper::Garbo = FontAwesomeHelper::CGarbo();

FontAwesomeHelper *FontAwesomeHelper::GetInstance()
{
    if (mInstance == nullptr) {
        static QMutex mtx;
        QMutexLocker locker(&mtx);
        if (mInstance == nullptr) {
            mInstance = new FontAwesomeHelper();
        }
    }
    return mInstance;
}

// 不用指针
//FontAwesomeHelper &FontAwesomeHelper::Instance()
//{
//    static FontAwesomeHelper instance;
//    return instance;
//}

void FontAwesomeHelper::SetIcon(QWidget *widget, const QString &iconName, int iconSize, const QColor &color)
{
    mFont.setPointSize(iconSize);
    if (widget) {
        widget->setFont(mFont);
        if (color.isValid()) {
            widget->setStyleSheet(QString("color:%1").arg(color.name()));
        }
        QLabel *label = qobject_cast<QLabel *>(widget);
        if (label) {
            label->setText(mIconUnicodeMap[iconName]);
        }
        QAbstractButton *button = qobject_cast<QAbstractButton *>(widget);
        if (button) {
            button->setText(mIconUnicodeMap[iconName]);
        }
    }
}

FontAwesomeHelper::FontAwesomeHelper()
{
    //2   1和2两种二选一 因为我们这里是指针，需要delete，如果不是指针，可以不用这么麻烦
    static CGarbo Garbo;
    QString ttfFile = ":/fontawesome-webfont.ttf";
    QString cssFile = ":/font-awesome.css";
    int fontId = QFontDatabase::addApplicationFont(ttfFile);
    qDebug() << fontId;
    QStringList fontFamily = QFontDatabase::applicationFontFamilies(fontId);
    Q_ASSERT(fontFamily.size() > 0);
    mFont.setFamily(fontFamily.at(0));
    Q_ASSERT(QFileInfo(cssFile).exists());
    QFile fontCssFile(cssFile);
    if (fontCssFile.open(QFile::Text | QFile::ReadOnly)) {
        while(!fontCssFile.atEnd()) {
            QString line = fontCssFile.readLine();
            if (line.contains(".fa-") && line.contains(":before")) {
                QString nextLine = fontCssFile.readLine();
                if (nextLine.contains("content")) {
                    QString key = line.split(":")[0].remove(".fa-");
                    QString content = nextLine.split(":")[1].remove(";").remove("\"").remove("\\");
                    mIconUnicodeMap.insert(key, content);
                }
            }
        }
    }
//    for(auto iter = mIconUnicodeMap.begin(); iter != mIconUnicodeMap.end(); iter++) {
//        QString key = iter.key();
//        qDebug() << key << iter.value();
//    }
}

QChar FontAwesomeHelper::IconUnicode(const QString &iconName)
{
    for(auto iter = mIconUnicodeMap.begin(); iter != mIconUnicodeMap.end(); iter++) {
        if(iter.key() == iconName) {
            bool ok;
            QString content = iter.value();
            QChar c = QString(content).toInt(&ok, 16);
            return c;
        }
    }
}

void FontAwesomeHelper::ShowHelper()
{
    mShowFontAswsome = std::make_shared<FontAwesomeShowForm>();
    mShowFontAswsome->show();
}
