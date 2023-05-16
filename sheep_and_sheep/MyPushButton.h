#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //    explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数,参数:正常的图片路径,按下后的图片路径
    MyPushButton(QString normal,QString press="");
    QString normal_img;//正常路径
    QString press_img;//按下后的路径
    void move1(int val);//移动函数

signals:

};

#endif // MYPUSHBUTTON_H



