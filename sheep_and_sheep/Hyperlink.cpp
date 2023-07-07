#include "Hyperlink.h"
#include "ui_Hyperlink.h"
#include "menu.h"
#include "loadPic.h"
#include <QThread>

Hyperlink::Hyperlink(int * _p_left_time,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Hyperlink),
    p_left_time(_p_left_time)
{
    qDebug() << "Hyperlink constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/main_menu.jpg";
    setup_background(ui, this, "次数用完了", pic_dir, 240, 100);
    const char * label_pic_dir = ":/new/prefix1/pictures/white.jpg";
    ui->label->setStyleSheet(label_pic_dir);

    //QLabel *linkLabel1 = new QLabel(this);
    ui->label->setOpenExternalLinks(true);//设置为true才能打开网页
    ui->label->setText("<a style='color: red; text-decoration: none' href = https://www.baidu.com=lately>获得两次机会");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->installEventFilter(this);

}

Hyperlink::~Hyperlink()
{
    qDebug() << "Hyperlink destructed";
    delete ui;
}

bool Hyperlink::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            (*p_left_time)+=2;
        }
    }
}
