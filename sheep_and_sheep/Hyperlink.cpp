#include "Hyperlink.h"
#include "ui_Hyperlink.h"
#include "menu.h"
#include "loadPic.h"
#include <QThread>
#include <QDesktopServices>

const char * github_link = "https://github.com/Phoenix-PKU/PracticeofProgramming";
const char * bilibili_link = "https://www.bilibili.com/video/BV1cX4y1e7cH";

Hyperlink::Hyperlink(int * _p_left_time,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hyperlink),
    p_left_time(_p_left_time)
{

    qDebug() << "Hyperlink constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/warning.jpg";
    setup_background(ui, this, "次数用完了, 你还想要更多的道具吗?😏", pic_dir, 400, 250);

    int x_scale,y_scale;
    QImage *yes= new QImage();
    yes->load(":/new/prefix1/pictures/confirm/yes.png");

    //QLabel *linkLabel1 = new QLabel(this);

    ui->label->setOpenExternalLinks(true);//设置为true才能打开网页
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->installEventFilter(this);
    ui->label->setStyleSheet("QLabel{border-image:url(:/new/prefix1/pictures/confirm/yes.png);}");
    ui->no->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/pictures/confirm/no.png);}");
}

Hyperlink::~Hyperlink()
{
    // qDebug() << "Hyperlink destructed";
    delete ui;
}

bool Hyperlink::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            (*p_left_time) += 1;
            QDesktopServices::openUrl(QUrl(github_link));
            QDesktopServices::openUrl(QUrl(bilibili_link));
            accept();
        }
    }
    return false;
}
void Hyperlink::on_no_clicked()
{
    accept();
}
