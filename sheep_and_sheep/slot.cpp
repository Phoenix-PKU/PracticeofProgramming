#include "slot.h"
#include "card.h"
#include <iostream>
#include <cassert>


Slot::Slot(int max_size):size(max_size)
{
    std::cout << "Hello from Slot with size " << max_size << std::endl;
    curr_size = 0;
}

Slot::~Slot(void){
    std::cout << "Bye from Slot with size " << size << std::endl;
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
void Slot::remove_cards(std::vector<Card *>::iterator card_it){
    std::vector<Card *>::iterator card_one = card_it, 
                            card_two = card_one + 1,
                            card_three = card_one + 2;
    /* cards should be in the slots. */
    assert (card_one >= cards.begin() && 
            card_three < cards.end());
    /* cards should be the same kind. */
    assert ((*card_one)->name == (*card_two)->name &&
            (*card_one)->name == (*card_three)->name);
    /*
    
    // This part should be the GUI of removing cards.

    */

    for (int i = 0;i < TRIPLE;i ++){
        Card * card_to_remove = *card_one;
        assert(card_to_remove->check_card_type(SlotCard));
        card_to_remove->set_card_type(EliminatedCard);
        card_one = cards.erase(card_one);
        curr_size --;
    }
    return ;
}

/* This function insert card into the place in the slot. */
void Slot::insert_card(Card * card, std::vector<Card *>::iterator place){
    assert (!slot_full());
    assert (card->check_card_type(ClickableCard));

    /* 
    
        This part should be the gui of inserting.
    
    */
    card->set_card_type(SlotCard);
    cards.insert(place, card);
    curr_size ++;

    return ;
}

/* This function prints the slot and is only used for debug. */
void Slot::print_slot(void){
    printf("slot with max size %d, current size %d\n", size, curr_size);
    int idx = 0;
    for (auto ip = cards.begin();ip != cards.end();ip ++){
        Card * card = *ip;
        printf("card %d: ", ++idx);
        card->print_card();
    }
}

