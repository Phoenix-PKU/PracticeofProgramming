#include <QPushButton>
#include <QPropertyAnimation>
#include <QThread>
#include <QGraphicsDropShadowEffect>
#include "game.h"
#include "ui_game.h"
#include "menu.h"
#include "loadPic.h"
#include "ConfirmBox.h"
#include "GameOverBox.h"
#include "progressbar.h"
#include <random>

#define ANI_TIME    100
template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end);
/* given an idx, find the type of the card to be put in the heap. */
static int get_type(int randidx, std::vector<int> & _cards_left,int & _ncard);

class Slot;
Game::Game(int _card_num, int _card_types,int _cards_in_heap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    card_nums(_card_num),
    card_types(_card_types),
    cards_in_heap(_cards_in_heap)
{
    length = 15 * CARD_SIZE;
    width = 11 * CARD_SIZE;
    /* max number of card that can appear on one line. */
    max_num_card = 13; 
    qDebug() << "Game constructed";
    const char * pic_dir = ":/new/prefix1/pictures"
                            "/background_picture/grassland.png";
    setup_background(ui, this, "羊了个羊游戏", pic_dir, length, width);
    
    //初始化进度条
    move = new Bar("Move", 0, this);
    cover = new Bar("Cover", BAR_LEN, this);
    move->show();
    cover->show();


    std::random_device rd;
    slot = new Slot(this);

    int idx;
    int ncard=card_nums; //剩余未放置的卡牌总数
    std::vector<int> cards_left; //剩余每个类未放置卡牌的个数
    for (int i=0;i<card_types;++i){
        cards_left.push_back(card_nums/card_types);
    }
    for (idx=0; idx < cards_in_heap; ++idx){
        int temp=rd();
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP1_X, HEAP1_Y,
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (idx=_cards_in_heap; idx < 2*cards_in_heap; ++idx){
        int temp=rd();
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP2_X, HEAP2_Y,
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (idx = 2 * cards_in_heap; idx < card_nums; ++idx) {
        int posx = (rd() % max_num_card + 4) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 3.5) * MCARD_SIZE;
        int temp=rd();
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  posx, posy,
                                  all_cards, this);
        all_cards.push_back(new_card);
    }

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card(true, "");
        connect(card, &QPushButton::clicked,
                this, [=](){update(card);});
    }

    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
    this -> consistency_check();
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

    cover->hide();
    move->set_len((double)BAR_LEN * (card_nums - cards_clickable)
                                    / card_nums);
    cover->show();

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
    this -> consistency_check();
}

/* This function choose the last card in the slot and put it back 
    to clickable card. 
    It wouldn't work if there is no card in the slot.
    The card will be put back to where it belongs.
*/
void Game::on_retreat_clicked(){
    // check condition
    qDebug() << "retreat one card";
    if (cards_in_slot == 0) {
        qDebug() << "no card to retreat!";
        return;
    }

    //update slot
    slot->print_slot();
    Card * to_retreat = slot -> get_last_card();
    assert (to_retreat->check_card_type(SlotCard));
    slot -> remove_last_card();
    
    //update game
    cards_in_slot--;
    cards_clickable++;
    //update progressbar
    cover->hide();
    move->set_len((double)BAR_LEN * (card_nums - cards_clickable)
                  / card_nums);
    cover->show();

    //do animation
    QPropertyAnimation *animation = new QPropertyAnimation(to_retreat, "geometry");
    animation_helper(animation, ANI_TIME, to_retreat->geometry(),
            QRect(to_retreat->get_orix(), to_retreat->get_oriy(), 
            CARD_SIZE,  CARD_SIZE));
    
    //update card
    to_retreat->set_posx(to_retreat->get_orix());
    to_retreat->set_posy(to_retreat->get_oriy());
    to_retreat->set_card_type(ClickableCard);
    to_retreat->setNormalBackground();
    to_retreat->setEnabled(true);
    to_retreat->print_card(true, "");
    //raise it to the upmost layer
    to_retreat->raise();

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * old_card = *ip;
        if (old_card->check_card_type(SlotCard) ||
            old_card->check_card_type(EliminatedCard))
            continue;
        if (old_card == to_retreat) continue;
        if (overlap(old_card, to_retreat)){
            cover_card(to_retreat, old_card);
        }
    }

    this->consistency_check();
}

void Game::on_myshuffle_clicked()
{
    qDebug() << "shuffle cards";
    std::vector<Card *>::iterator card_i;
    std::vector<int>::iterator p_temp;
    std::vector<int> temp;

    // pick up all cards that is clickable or covered
    // delete them and put them into temp.

    for (card_i=all_cards.begin();card_i!=all_cards.end();){
        if ((!(*card_i)->in_heap) && ((*card_i)->check_card_type(ClickableCard)
               ||(*card_i)->check_card_type(CoveredCard))){
            temp.push_back((*card_i)->nametoint());
            delete (*card_i);
            card_i=all_cards.erase(card_i);
        }
        else{
            ++card_i;
        }
    }

    // create new cards that has random position

    std::random_device rd;
    for (p_temp=temp.begin();p_temp!=temp.end();++p_temp){
        int posx = (rd() % max_num_card + 4) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 3.5) * MCARD_SIZE;
        Card * new_card = new Card(card_name[*p_temp],
                                  posx, posy,
                                  all_cards, this);
        connect(new_card, &QPushButton::clicked, this, 
                [=](){update(new_card);});
        all_cards.push_back(new_card);
    }

    // set background and enable of new cards.
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if(card -> check_card_type(ClickableCard)){
            card->setNormalBackground();
            card->setEnabled(true);
        }
        else if(card -> check_card_type(CoveredCard)){
            card->setDarkBackground();
            card->setEnabled(false);
        }
    }

    this->consistency_check();
}

template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end){
    ani->setDuration(dur);
    ani->setStartValue(start);
    ani->setEndValue(end);
    ani->start();
}

void Game::consistency_check(void){
    slot -> slot_concheck(cards_in_slot);
    int real_clickable = 0, real_in_slot = 0, real_eliminate = 0;
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card -> cardconcheck();
        if (card->check_card_type(ClickableCard) || card->check_card_type(CoveredCard))
            real_clickable ++;
        else if (card->check_card_type(SlotCard)){
            real_in_slot ++;
        }
        else if (card->check_card_type(EliminatedCard)){
            real_eliminate ++;
        }
    }
    assert (real_clickable == cards_clickable);
    assert (real_in_slot == cards_in_slot);
    assert (real_eliminate == cards_eliminate);
}


static int get_type(int randidx, std::vector<int> & _cards_left,int & _ncard){
    int temp=randidx%_ncard,n=0;
    for(std::vector<int>::iterator p = _cards_left.begin();p!=_cards_left.end();++p){
        n+=*p;
        if (temp < n){
            (*p)--;
            --_ncard;
            return p-_cards_left.begin();
        }
    }
}



