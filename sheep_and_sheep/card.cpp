#include "card.h"
#include <iostream>
#include <cstring>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <cassert>
#include <vector>
#include <math.h>
#include "game.h"

#define MAXLINE 128
#define MAX_LENGTH_NAME 10

class Game;
const int max_type_of_cards = 100;

const char * card_name[max_type_of_cards] =
        {"Carrot", "Grass", "Corn", "Bucket", "Bell", "Stump",
         "Ball", "Cotton", "Fire", "Scissor", "Bottle", "Brush",
         "Cabbage", "Glove", "Fork"};
const int current_type_of_cards = sizeof(card_name) 
    / sizeof(const char *);

unsigned long long Card::ID = 0;

static void setup_card(Card * card, int posx, int posy, 
    const char * pic_dir, std::string uid);

/* This function construct a card with name(_name), all_cards 
 * is for implementing covering and should not be changed by
 * this function. */
Card::Card(const char * _name, int _posx, int _posy,
    const std::vector<Card *> all_cards, QDialog * parent,int _in_heap):
    name(_name),
    QPushButton(parent), 
    posx(_posx), posy(_posy),
    orix(_posx), oriy(_posy),
    in_heap(_in_heap)
{
    game = (Game *) parent;
    char buf[MAXLINE], pic_dir[MAXLINE];
    sprintf(buf, "%llu", ID++);
    uid = std::string(buf);
    type = ClickableCard;

    
    strcpy(pic_dir, ":/new/prefix1/pictures/card_picture/");
    strcpy(pic_dir + strlen(pic_dir), name);
    strcpy(pic_dir + strlen(pic_dir), ".png");
    setup_card(this, posx, posy, pic_dir, uid);

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * old_card = *ip;
        if (old_card->check_card_type(SlotCard) ||
            old_card->check_card_type(EliminatedCard))
            continue;
        if (overlap(old_card, this)){
            cover_card(this, old_card);
        }
    }
}

int Card::nametoint(void){
    for (int i = 0;i < current_type_of_cards;++i){
        if (strcmp(name,card_name[i])==0){
            return i;
        }
    }
    assert (false);
}

Card::~Card(void){
    qDebug() << "Goodbye from card "; 
    ID--;
}

/* This function crashs a card. 
 * It may be covered by other cards. 
 * This function is called by game::crash. */
void Card::crash_card(void){
    assert (check_card_type(ClickableCard) ||
            check_card_type(CoveredCard));

    for (auto it = covering.begin();it != covering.end();it++){
        Card * lower_card = *it;
        lower_card -> remove_upper_card(this);
    } covering.clear();

    for (auto it = covered.begin();it != covered.end();it ++){
        Card * upper_card = *it;
        upper_card -> remove_lower_card(this);
    } covered.clear();

    posx = INVALID_XPOS;
    posy = INVALID_YPOS;
    type = EliminatedCard;
    this->hide();
}

/* This function removes the card from the top and 
 * remove itself from the cards that is covered by itself. */
void Card::remove_card(void){
    print_card(true, "");
    assert (check_card_type(ClickableCard));
    assert (covered.empty());
    for (auto it = covering.begin();it != covering.end();it ++){
        Card * lower_card = *it;
        lower_card -> remove_upper_card(this);
    }
    covering.clear();
}

/* This function remove upper_card that is currently covering
 * this card, if there is no card aftering removing, make it
 * clickable. */
void Card::remove_upper_card(Card * upper_card){
    assert (check_card_type(CoveredCard));
    auto it = std::find(covered.begin(), covered.end(), upper_card);
    assert (it != covered.end());
    covered.erase(it);
    if (covered.empty()){
        this->set_card_type(ClickableCard);
        this->setNormalBackground();
        this->setEnabled(true);
    }
}

/*
    This function remove lower card that is currently 
    covered by this card. 
*/
void Card::remove_lower_card(Card * lower_card){
    assert (lower_card->check_card_type(CoveredCard));
    auto it = std::find(covering.begin(), covering.end(), lower_card);
    assert (it != covering.end());
    covering.erase(it);
}
/*
 if cover_flag is true, then print all cards that are covering 
 it or are covered by it.
*/
void Card::print_card(bool cover_flag, const char * prefix){
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
    else if (type == CoveredCard){
        card_type = "CoveredCard";
    }
    else {
        qDebug() << "unknown card type " << type;
        assert(false);
    }
    qDebug() << prefix << "uid: " << uid.c_str()
             << ", name: " << name
             << ", type is: " << card_type.c_str()
             << "xpos = " << posx << ", ypos = " << posy;
    /*
    if (cover_flag){
        qDebug() << " begin covering card: ";
        for (auto ip = covering.begin();ip != covering.end();ip ++){
            (*ip)->print_card(false, "    ");
        }
        qDebug() << " begin covered card: ";
        for (auto ip = covered.begin();ip != covered.end();ip ++){
            (*ip)->print_card(false, "    ");
        }
    }*/
}

static void setup_card(Card * card, int posx, int posy, 
    const char * pic_dir, std::string uid){
    card->setGeometry(posx, posy, CARD_SIZE, CARD_SIZE);
    //设置按钮对象名字
    card->setObjectName("card_" + uid);
    //设置按钮图像
    card->setNormalBackground();
    card->show();
}

void cover_card(Card * upper_card, Card * lower_card){
    assert (upper_card -> check_card_type(ClickableCard));


    upper_card -> covering.push_back(lower_card);
    lower_card -> covered.push_back(upper_card);

    lower_card -> set_card_type(CoveredCard);
    lower_card -> setDarkBackground();
    lower_card -> setEnabled(false);
}

bool overlap(Card * old_card, Card * new_card){
    return abs(old_card -> posx - new_card -> posx) < CARD_SIZE
        && abs(old_card -> posy - new_card -> posy) < CARD_SIZE;
}

void Card::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);//绘制样式
}

void Card::setNormalBackground(){
    char arg[MAXLINE];
    strcpy(arg, "QPushButton{border-image: url("
                ":/new/prefix1/pictures/card_picture/");
    strcpy(arg + strlen(arg), name);
    strcpy(arg + strlen(arg), ".png);}");
    this->setStyleSheet(arg);
}

void Card::setDarkBackground(){
    char arg[MAXLINE];
    strcpy(arg, "QPushButton{border-image: url("
                ":/new/prefix1/pictures/card_picture/");
    strcpy(arg + strlen(arg), name);
    strcpy(arg + strlen(arg), "-dark.png);}");
    this->setStyleSheet(arg);
}

void Card::cardconcheck(void){
    if (type != EliminatedCard){
        //assert (posx == this -> pos().x());
        //assert (posy == this -> pos().y());
    }
    for (auto ip = covering.begin();ip != covering.end();ip++){
        Card * card = *ip;
        assert (overlap(card, this));
    }
    for (auto ip = covered.begin();ip != covered.end();ip ++){
        Card * card = *ip;
        assert (overlap(card, this));
    }
    if (type == ClickableCard){
        assert (orix == posx && oriy == posy);
    }
    else if (type == SlotCard){
        
    }
    else if (type == EliminatedCard){
        assert (posx == INVALID_XPOS && posy == INVALID_YPOS);
    }
    else if (type == CoveredCard){
        assert (orix == posx && oriy == posy);
    }
    else {
        qDebug() << "unknown card type " << type;
        assert(false);
    }
}

bool Card::event(QEvent *event){
    if(this->type == ClickableCard)
    {
        if(event->type() == QEvent::Enter)
            this->setGeometry(posx - 0.1 * CARD_SIZE, posy - 0.1 * CARD_SIZE,
                              1.2 * CARD_SIZE, 1.2 * CARD_SIZE);
        if(event->type() == QEvent::Leave)
            this->setGeometry(posx, posy, CARD_SIZE, CARD_SIZE);
    }
    return QPushButton::event(event);
}
