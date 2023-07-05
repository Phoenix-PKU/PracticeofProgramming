#include <cassert>
#include <QPropertyAnimation>
#include <QDebug>
#include "slot.h"
#include "card.h"
#include "game.h"

#define ANI_TIME    100

template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end);

class Game;
Slot::Slot(Game * _game, int max_size):
    size(max_size),
    game(_game)
{
    qDebug() << "Hello from Slot with size " << max_size << "\n";
    curr_size = 0;
}

Slot::~Slot(void){
    qDebug() << "Bye from Slot with size " << size << "\n";
}

/* This function find the target slot when card is added into 
 * the slot. 
 * The rule are the same as the wechat mini game.
 * | 1 | 2 | e | e | e | e | e |
 * and a card one comes along, then it will be inserted between
 * 1 and 2. */
std::vector<Card *>::iterator Slot::find_slot(Card * card){
    for (auto ip = cards.begin();ip != cards.end();ip ++){
        Card * prev_card = *ip;
        if (prev_card->name == card->name){
            while (ip != cards.end() && card->name == prev_card->name){
                ip++;
                prev_card = *ip;
            }

            for (auto it = ip; it != cards.end(); ++it) {
                Card * tmp = *it;
                QPropertyAnimation * animation = new QPropertyAnimation(tmp, "geometry");
                animation_helper(animation, ANI_TIME, tmp->geometry(), 
                    QRect(YPOS, tmp->pos().y()+CARD_SIZE, CARD_SIZE, CARD_SIZE));
                /*
                animation->setDuration(ANI_TIME);
                animation->setStartValue(tmp->geometry());
                animation->setEndValue(QRect(YPOS, tmp->pos().y()+CARD_SIZE, CARD_SIZE, CARD_SIZE));
                animation->start();
                */
            }

            return ip;
        }
    }
    return cards.end();
}

/* This function check whether there is a TRIPLE in the slot. 
 * If so, return the iterator of the first card. */
std::vector<Card *>::iterator Slot::check_slot(void){
    for (auto ip = cards.begin();ip <= cards.end() - TRIPLE;ip ++){
        std::vector<Card *>::iterator card_one = ip, 
                        card_two = card_one + 1,
                        card_three = card_one + 2;
        if((*card_one)->name == (*card_two)->name &&
            (*card_one)->name == (*card_three)->name){
            return card_one;
        }
    }
    return cards.end();
}

bool Slot::can_remove(void){
    std::vector<Card *>::iterator to_remove = check_slot();
    return to_remove != cards.end();
}

/* This function remove three cards start from start. */
void Slot::remove_cards(std::vector<Card *>::iterator card_it, bool win){
    std::vector<Card *>::iterator card_one = card_it, 
                            card_two = card_one + 1,
                            card_three = card_one + 2;
    /* cards should be in the slots. */
    assert (card_one >= cards.begin() && 
            card_three < cards.end());
    /* cards should be the same kind. */
    assert ((*card_one)->name == (*card_two)->name &&
            (*card_one)->name == (*card_three)->name);

    for (int i = 0;i < TRIPLE;i ++){
        Card * card_to_remove = *card_one;
        assert(card_to_remove->check_card_type(SlotCard));
        card_to_remove->set_card_type(EliminatedCard);
        card_one = cards.erase(card_one);
        curr_size --;
        QPropertyAnimation *animation = new QPropertyAnimation(card_to_remove, "geometry");
        int ani_time = win?0:ANI_TIME;
        animation_helper(animation, ani_time, card_to_remove->geometry(),
            QRect(YPOS, -CARD_SIZE * 2, CARD_SIZE,  CARD_SIZE));
        /*
        animation->setDuration(ANI_TIME);
        animation->setStartValue(card_to_remove->geometry());
        animation->setEndValue(QRect(YPOS, -ANI_TIME, CARD_SIZE, CARD_SIZE));
        animation->start();
        */
    }

    for (auto ip = card_one;ip != cards.end();ip ++){
        Card * tmp = *ip;
        QPropertyAnimation *animation = new QPropertyAnimation(tmp, "geometry");
        animation_helper(animation, ANI_TIME, tmp->geometry(),
            QRect(YPOS, tmp->pos().y()-3 * CARD_SIZE, CARD_SIZE,  CARD_SIZE));
        /*
        animation->setDuration(ANI_TIME);
        animation->setStartValue(tmp->geometry());
        animation->setEndValue(QRect(YPOS, tmp->pos().y()-3 * CARD_SIZE, CARD_SIZE, CARD_SIZE));
        animation->start();
        */
    }
    return ;
}

Card * Slot::get_last_card(void)
{
    if (cards.empty()) return NULL;
    return *cards.rbegin();
}

/* This function insert card into the place in the slot. */
void Slot::insert_card(Card * card, std::vector<Card *>::iterator place){
    assert (!slot_full());
    assert (card->check_card_type(ClickableCard));
    
    card->set_card_type(SlotCard);
    //card->setStyleSheet("background-color: rgba(255, 255, 255, 50%);");
    card->setEnabled(false);
    cards.insert(place, card);
    curr_size ++;

    int where_to_go = this->find_slot(card) - this->begin() - 1;
    QPropertyAnimation * animation = new QPropertyAnimation(card, "geometry");
    game->connect(animation, &QPropertyAnimation::finished,
        game, [=](){game->update_tail();});
    animation_helper(animation, ANI_TIME, card->geometry(),
        QRect(YPOS, CARD_SIZE * where_to_go, CARD_SIZE,  CARD_SIZE));
/*
    animation->setDuration(ANI_TIME);
    animation->setStartValue(card->geometry());
    animation->setEndValue(QRect(YPOS, CARD_SIZE * where_to_go, CARD_SIZE, CARD_SIZE));
    animation->start();
*/
}

/* This function prints the slot and is only used for debug. */
void Slot::print_slot(void){
    qDebug() << "slot with max size " << size
             << ", current size " << curr_size;
    int idx = 0;
    for (auto ip = cards.begin();ip != cards.end();ip ++){
        Card * card = *ip;
        qDebug() << "card " << ++idx << ": ";
        card->print_card(true, "");
    }
    qDebug() << "end print slot\n";
}

template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end){
    ani->setDuration(dur);
    ani->setStartValue(start);
    ani->setEndValue(end);
    ani->start();
}
