#include "gamestate.h"
#include "slot.h"
#include "card.h"
#include <cassert>
#include <QDialog>

extern const int current_type_of_cards;

Gamestate::Gamestate(int card_nums, int card_types)
{
    assert (card_nums > 0 && card_types > 0);
    /* card_nums should be multiple of card_types. */
    assert (card_nums % card_types == 0 &&
            (card_nums / card_types) % 3 == 0);
    /* card_nums should be no more than current types. */
    assert (card_nums <= current_type_of_cards);


    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
    game_over = false;
}

/* This function is called when user clicked on this 
 * card. */
void Gamestate::update(){
    cards_clickable --;
    cards_in_slot ++;
    if (slot_full()){
        /*
        
        Maybe there will be some other things later on, 
        now just end the game.
        
        */
        game_end("fail");
    }
    if (all_cards_eliminate()){
        /* 
        
        GUI for winning.
        
        */
        game_end("win");
    }
    print_all_cards();
}

/* Ideally, this should return the card that the user clicks on, 
 * Now it just choose the first card that is */
int Gamestate::choose_one_card(void){
    /*
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if (card->check_card_type(ClickableCard)){
            qDebug() << "A card is successfully choosed";
            return card;
        }
    }
    // Should not fail to find one card.
    assert(false);
    return *all_cards.end();*/
    return 0;
}

/* This function print all cards in all_cards, 
 * this is only used for debug. */
void Gamestate::print_all_cards(void){
    /*for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card();
    }*/
}

void Gamestate::game_end(const char * status){
    assert (strcmp(status, "win") == 0
         || strcmp(status, "fail") == 0);
    game_over = true;
    if (strcmp(status, "win") == 0){
        qDebug() << "Eliminate all cards, Congrats!!!";
    }
    else if (strcmp(status, "fail") == 0){
        qDebug() << "The slot is full. You failed!!!";
    }
}

void Gamestate::run()
{
    qDebug() << "GameStateThread starts";

    while (!game_over){
        int target = choose_one_card();
        qDebug() << "the " << target << "th available card is chosen";
        emit sig_choose(target);
        update();
    }
}

Gamestate::~Gamestate()
{  

}

