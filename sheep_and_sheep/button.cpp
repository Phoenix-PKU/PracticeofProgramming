#include <QWidget>
#include "button.h"

MyButton::MyButton(QWidget *parent) : QPushButton(parent){
    resize(500,500);
    QPushButton *button1=new QPushButton;
    QPushButton *button2=new QPushButton;
    button1->setParent(this);
    button1->setText("Button1");
    button1->move(150,200);
    button2->setParent(this);
    button2->setText("Button2");
}
