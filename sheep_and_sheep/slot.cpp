#include "slot.h"
#include <iostream>

Slot::Slot(int max_size):size(max_size)
{
    std::cout << "Hello from Slot with size " << max_size << std::endl;
    curr_size = 0;
}

Slot::~Slot(void){
    std::cout << "Bye from Slot with size " << size << std::endl;
}

std::vector<Card *>::iterator Slot::find_slot(Card * card){
    return cards.begin();
}

std::vector<Card *>::iterator Slot::check_slot(void){
    return cards.begin();
}

void Slot::remove_cards(Card * start){
    return ;
}

void Slot::insert_card(Card * card, std::vector<Card *>::iterator place){
    return ;
}

