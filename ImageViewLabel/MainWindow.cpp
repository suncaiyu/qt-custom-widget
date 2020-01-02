#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ImageViewLabel.h"
#include "AdsWidget2.h"
#include "Win32GetDesktop.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    AdsWidget2 *ads = new AdsWidget2;
//    ImageViewLabel *imagelabel = new ImageViewLabel(this);
//    imagelabel->setGeometry(10, 10, 510, 208);
//    //添加自定义图片和文案描述
//    const QList<std::pair<QString, QString>> &&imagepairlst = {
//        std::make_pair(":/1.jpg", QString::fromLocal8Bit("刘强东很厉害！给雨田哥发个大红包！")),
//        std::make_pair(":/2.jpg",
//                       QString::fromLocal8Bit("这只是一条测试数据,快扫扫博主二维码打赏下！")),
//        std::make_pair(":/3.jpg", QString::fromLocal8Bit("What!博主这么辛苦，你还不打赏下！")),
//        std::make_pair(":/4.jpg",
//                       QString::fromLocal8Bit("What!博主这么辛苦，你还不打赏下！")),
//        std::make_pair(":/5.jpg",
//                       QString::fromLocal8Bit("欢迎扫雨田哥二维码进行打赏！")),
//    };

    //    imagelabel->addImage(imagepairlst);
        setCentralWidget(ads);
        /*启用下面代码可以使其变成windows桌面屏保*/
//       iniworker();
//       inisystem(this);
//       ShowOnDesktop(this);
}

MainWindow::~MainWindow()
{
    QuitonDesktop();
    delete ui;
}

