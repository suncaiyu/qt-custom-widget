#include "FontAwesomeShowForm.h"
#include "ui_FontAwesomeShowForm.h"
#include <FontAwesomeHelper.h>
#include <QStyle>
FontAwesomeShowForm::FontAwesomeShowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontAwesomeShowForm)
{
    ui->setupUi(this);
    mLayout = std::unique_ptr<QGridLayout>(new QGridLayout());
    ui->scrollAreaWidgetContents->setLayout(mLayout.get());
    Init();
}

FontAwesomeShowForm::~FontAwesomeShowForm()
{
    delete ui;
}

void FontAwesomeShowForm::Init()
{
    FontAwesomeHelper *helper = FontAwesomeHelper::GetInstance();
    QMap <QString, QString> map = helper->mIconUnicodeMap;
    QMap<QString, QString>::iterator it = map.begin();
    int count = 0;
    for (it; it != map.end(); it++) {
        ShowWidget *sw = new ShowWidget();
        sw->Set(it.key());
        int i = count / 3;
        int j = count % 3;
        mLayout->addWidget(sw, i, j);
        count++;
    }

    for (int k = 0; k <= 77; ++k) {
        ShowWidget *sw = new ShowWidget();
        enum QStyle::StandardPixmap Icon = (enum QStyle::StandardPixmap)k;
        sw->SetQtIcon(QString::number(k), style()->standardIcon(Icon).pixmap(25, 25));
        int i = count / 3;
        int j = count % 3;
        mLayout->addWidget(sw, i, j);
        count++;
    }
}

ShowWidget::ShowWidget(QWidget *parent)
{
    mLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout);
    setLayout(mLayout.get());
    mName = std::unique_ptr<QLabel>(new QLabel);
    mIcon = std::unique_ptr<QLabel>(new QLabel);
    mLayout->addWidget(mName.get());
    mLayout->addWidget(mIcon.get());
}

void ShowWidget::Set(QString s)
{
    mName->setText(s);
    FontAwesomeHelper *helper = FontAwesomeHelper::GetInstance();
    QFont font = helper->GetAwesomeFont();
    font.setPointSize(25);
    mIcon->setFont(font);
    mIcon->setText(helper->IconUnicode(s));
    mIcon->setStyleSheet("QLabel{color:red;}");
}

void ShowWidget::SetQtIcon(QString s, QPixmap pix)
{
    mName->setText(s);
    mIcon->setPixmap(pix);
}
