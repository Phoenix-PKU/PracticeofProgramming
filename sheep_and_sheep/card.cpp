#include "card.h"
//#include "uuid/uuid.h"
#include <iostream>
#include <cstring>
#include <QPropertyAnimation>
#include "child_menu.h"

#define MAX_ID  128
#define MAX_LENGTH_NAME  6
const int max_type_of_cards = 100;
const char * card_name[max_type_of_cards] = 
        {"Carrot", "Grass", "Corn", "Bucket"};
const int current_type_of_cards = sizeof(card_name) 
    / sizeof(const char *);

unsigned long long Card::lxid = 0;

Card::Card(const char * _name, int posx, int posy, QDialog * parent):
    name(_name),
    QPushButton(parent)
{
    /*uuid_t uuid;
    char buf[MAX_ID];
    uuid_generate(uuid);
    uuid_unparse(uuid, buf);
    uid = std::string(buf);*/
    char buf[MAX_ID];
    sprintf(buf, "%llu", lxid++);
    uid = std::string(buf);
    type = ClickableCard;

    qDebug() << "Construct card "; print_card();

    this->setGeometry(posx, posy, 50, 50);
    //设置按钮对象名字
    this->setObjectName("pushButton_card_" + uid);
    //设置按钮显示文本
    this->setText("kapai " + QString::fromStdString(uid)
                  + "\n" + QString::fromStdString(name));

    this->show();
}

Card::~Card(void){
    qDebug() << "Goodbye from card "; print_card();
    lxid--;
}

void Card::print_card(void){
    std::string card_type;
    if (type == ClickableCard){
        card_type = "ClickableCard";
    }
    else if (type == SlotCard){
        card_type = "SlotCard";
    }
    else if (type == EliminatedCard){
        card_type = "EliminatedCard";
    }
    else assert(false);
    qDebug() << "uid: " << uid.c_str()
             << ", name: " << name
             << ", type is: " << card_type.c_str();
}
/*
void Card::mousePressEvent(QMouseEvent * e) {
    //this->move(this->pos().x() + 10, this->pos().y() + 10);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(200, 100, 100, 100));
    animation->start();
}*/
