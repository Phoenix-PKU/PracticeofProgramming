#include "gamestate.h"
#include "slot.h"
#include "card.h"
#include <cassert>

extern const int current_type_of_cards;

Gamestate::Gamestate(int card_nums, int card_types){
    assert (card_nums > 0 && card_types > 0);
    /* card_nums should be multiple of card_types. */
    assert (card_nums % card_types == 0 &&
            (card_nums / card_types) % 3 == 0);
    /* card_nums should be no more than current types. */
    assert (card_nums <= current_type_of_cards);
    for (int i = 0;i < card_nums;i ++){
        Card * new_card = new Card(card_name[i % card_types]);
        all_cards.push_back(new_card);
    }
    slot = new Slot;
    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
}
/* This function control the main logic of the game,
 * which is a loop waiting for user to click and 
 * updating the status. */
void Gamestate::play(void){
    while (!game_over){
        Card * target = choose_one_card();
        update(target);
    }
    return ;
}
/* This function is called when user clicked on this 
 * card. */
void Gamestate::update(Card * card){
    std::vector<Card *>::iterator place = slot->find_slot(card);
    slot->insert_card(card, place);
    cards_clickable --;
    cards_in_slot ++;
    if (slot->can_remove()){
        std::vector<Card *>::iterator to_remove = slot->check_slot();
        slot->remove_cards(to_remove);
        cards_in_slot -= TRIPLE;
        cards_eliminate += TRIPLE;
    }
    if (slot->slot_full()){
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
    slot->print_slot();
}

/* Ideally, this should return the card that the user clicks on, 
 * Now it just choose the first card that is */
Card * Gamestate::choose_one_card(void){
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if (card->check_card_type(ClickableCard)){
            return card;
        }
    }
    /* Should not fail to find one card. */
    assert(false);
    return *all_cards.end();
}

/* This function print all cards in all_cards, 
 * this is only used for debug. */
void Gamestate::print_all_cards(void){
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card();
    }
}

void Gamestate::game_end(const char * status){
    assert (strcmp(status, "win") == 0
         || strcmp(status, "fail") == 0);
    game_over = true;
    if (strcmp(status, "win") == 0){
        printf("Eliminate all cards, Congrats!!!\n");
    }
    else if (strcmp(status, "fail") == 0){
        printf("The slot is full. You failed!!!\n");
    }
}

Gamestate::~Gamestate()
{  
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        delete card;
    }
    delete slot;
    all_cards.clear();
}
