#include <QPropertyAnimation>
#include <QThread>
#include <QGraphicsDropShadowEffect>
#include "game.h"
#include "ui_game.h"
#include "menu.h"
#include "loadPic.h"
#include "ConfirmBox.h"
#include "GameOverBox.h"
#include <random>

#define ANI_TIME    100
template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end);

class Slot;
Game::Game(int _card_num, int _card_types,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    card_nums(_card_num),
    card_types(_card_types)
{
    length = 16 * CARD_SIZE;
    width = 12 * CARD_SIZE;
    /* max number of card that can appear on one line. */
    max_num_card = 13; 
    qDebug() << "Game constructed";
    const char * pic_dir = "../../../../sheep_and_sheep/pictures"
                            "/background_picture/grassland.jpg";
    setup_background(ui, this, "羊了个羊游戏", pic_dir, length, width);
    
    std::random_device rd;
    slot = new Slot(this);
    for (int idx = 0; idx < card_nums; ++idx) {
        int posx = (rd() % max_num_card + 1) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 1) * MCARD_SIZE;
        Card * new_card = new Card(card_name[idx % card_types], 
            posx, posy, 
        all_cards, this);
        all_cards.push_back(new_card);
    }

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card(true, "");
        if (card -> check_card_type(ClickableCard))
            connect(card, &QPushButton::clicked,
                this, [=](){update(card);});
        else{
            card->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");  
            // 设置背景色为半透明的黑色
            card->setEnabled(false);
        }
    }

    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;

}

Game::~Game()
{
    qDebug() << "Game destructed";
    delete ui;
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        delete card;
    }
    all_cards.clear();
    delete slot;
}

void Game::on_confirmBox_clicked(){
    qDebug() << "Are you sure to quit";
    ConfirmBox confirmbox;
    if(confirmbox.exec()==ConfirmBox::Accepted){
        accept();
    }
}

void Game::update(Card * chosen){
    qDebug() << "------\nCard "<< chosen->get_id() <<" is clicked\n------";

    cards_clickable --;
    cards_in_slot ++;
    chosen->remove_card();
    std::vector<Card *>::iterator place = slot->find_slot(chosen);
    int where_to_go = place - slot->begin();
    slot->insert_card(chosen, place);
/*
    QPropertyAnimation * animation = new QPropertyAnimation(chosen, "geometry");
    connect(animation, &QPropertyAnimation::finished,
            this, [=](){update_tail();});
    animation->setDuration(100);
    animation->setStartValue(chosen->geometry());
    animation->setEndValue(QRect(YPOS, 50 * where_to_go, 50, 50));
    animation->start();
*/
}

void Game::update_tail() {
    if (slot->can_remove()){
        std::vector<Card *>::iterator to_remove = slot->check_slot();
        cards_in_slot -= TRIPLE;
        cards_eliminate += TRIPLE;
        slot->remove_cards(to_remove, all_cards_eliminate());
        qDebug() << "Removing three cards\n";

    }

    slot->print_slot();

    if(slot->slot_full()) {
        qDebug() << "The slot is full. You failed!!!";
        GameOverBox GameOverBox("fail");
        if((GameOverBox.exec()==ConfirmBox::Accepted)){
            accept();
        }
    }

    if(all_cards_eliminate()) {
        qDebug() << "Eliminate all cards, Congrats!!!";
        GameOverBox GameOverBox("win");
        if((GameOverBox.exec()==ConfirmBox::Accepted)){
            accept();
        }
    }
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        (*ip)->print_card(true, "");
    }
}
void Game::on_myshuffle_clicked()
{
    qDebug() << "shuffle cards";
    std::vector<Card *>::iterator card_i;
    std::vector<int>::iterator p_temp;
    std::vector<int> temp;
    for (card_i=all_cards.begin();card_i!=all_cards.end();){
        if ((*card_i)->check_card_type(ClickableCard)||(*card_i)->check_card_type(CoveredCard)){
            temp.push_back((*card_i)->nametoint());
            delete (*card_i);
            card_i=all_cards.erase(card_i);
        }
        else{
            ++card_i;
        }
    }
    std::random_device rd;
    for (p_temp=temp.begin();p_temp!=temp.end();++p_temp){
        int posx = (rd() % max_num_card + 1) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 1) * MCARD_SIZE;
        Card * new_card = new Card(card_name[*p_temp],
                                  posx, posy,
                                  all_cards, this);
        all_cards.push_back(new_card);
    }
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card(true, "");
        if (card -> check_card_type(ClickableCard))
            connect(card, &QPushButton::clicked,
                    this, [=](){update(card);});
        else if(card -> check_card_type(CoveredCard)){
            card->setStyleSheet("background-color: rgba(0, 0, 0, 100%);");
            // 设置背景色为半透明的黑色
            card->setEnabled(false);
        }
    }

}

template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end){
    ani->setDuration(dur);
    ani->setStartValue(start);
    ani->setEndValue(end);
    ani->start();
}

/*
void Game::receive_sig_choose(int target) {
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if (card->check_card_type(ClickableCard)){
            qDebug() << "--------\nA card is successfully choosed\n--------";

            std::vector<Card *>::iterator place = slot->find_slot(card);
            slot->insert_card(card, place);

            if (slot->can_remove()){
                std::vector<Card *>::iterator to_remove = slot->check_slot();
                slot->remove_cards(to_remove);
                emit sig_remove();
            }

            slot->print_slot();
            return;
        }
    }
}*/
