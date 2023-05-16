#include "MyPushButton.h"
#include <QDebug>
#include <QPoint>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
void MyPushButton::move1(int val)
{
    QPoint w = this->pos();
    w.setY(w.y()+val);
    this->move(w);
    qDebug() << "啥玩意" << val ;
}

MyPushButton::MyPushButton(QString nor,QString pre)
{
    resize(500,500);
    this->normal_img = nor;
    this->press_img = pre;

    QPixmap map;
    bool YES = map.load(nor);
    if( !YES )
    {
        qDebug() << "图片加载失败";
        return;
    }
    //设置图片大小
    this->setFixedSize(map.width(),map.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图片
    this->setIcon(map);
    //设置图标大小
    //    this->setIconSize(QSize(map.width(),map.height()));
}


