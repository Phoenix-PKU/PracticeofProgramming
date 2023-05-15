#include "gamestate.h"
#include "slot.h"
#include "card.h"

Gamestate::Gamestate(int card_nums){
    for (int i = 0;i < card_nums;i ++){
        Card * new_card = new Card;
        all_cards.push_back(new_card);
    }
    slot = new Slot;
}

void Gamestate::play(void){
    while (!game_over){
        /* waitForClick. */
        /* Update status. */
        if (true)
            break;
    }
    return ;
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
