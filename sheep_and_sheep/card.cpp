#include "card.h"
//#include "uuid/uuid.h"
#include <iostream>
#include <cstring>
#include <QPropertyAnimation>
#include "game.h"

#define MAXLINE 128
#define MAX_LENGTH_NAME  6


const int max_type_of_cards = 100;

const char * card_name[max_type_of_cards] =
        {"Carrot", "Grass", "Corn", "Bucket", "Bell", "Stump"};
const int current_type_of_cards = sizeof(card_name) 
    / sizeof(const char *);

unsigned long long Card::ID = 0;

static void setup_card(Card * card, int posx, int posy, 
    const char * pic_dir, std::string uid);

Card::Card(const char * _name, int _posx, int _posy, QDialog * parent):
    name(_name),
    QPushButton(parent), 
    posx(_posx), posy(_posy),
    orix(_posx), oriy(_posy)
{
    /*uuid_t uuid;
    char buf[MAX_ID];
    uuid_generate(uuid);
    uuid_unparse(uuid, buf);
    uid = std::string(buf);*/
    
    char buf[MAXLINE], pic_dir[MAXLINE];
    sprintf(buf, "%llu", ID++);
    uid = std::string(buf);
    type = ClickableCard;

    qDebug() << "Construct card "; print_card();
    strcpy(pic_dir, "../../../../sheep_and_sheep/pictures/card_picture/");
    strcpy(pic_dir + strlen(pic_dir), name);
    strcpy(pic_dir + strlen(pic_dir), ".jpg");
    setup_card(this, posx, posy, pic_dir, uid);
}

Card::~Card(void){
    qDebug() << "Goodbye from card "; print_card();
    ID--;
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

static void setup_card(Card * card, int posx, int posy, 
    const char * pic_dir, std::string uid){
    
    card->setGeometry(posx, posy, CARD_SIZE, CARD_SIZE);
    //设置按钮对象名字
    card->setObjectName("card_" + uid);
    QPixmap pix;
    pix.load(pic_dir);//加载图片
    pix = pix.scaled(card->size());//改变图片大小
    card->setFixedSize(pix.width(),pix.height());//调整按钮大小
    card->setStyleSheet("QPushButton{border:0px;}");//调整无边框
    card->setIcon(pix);//设置按钮图像
    card->setIconSize(QSize(pix.width(),pix.height()));//设置图像大小
    card->show();
}