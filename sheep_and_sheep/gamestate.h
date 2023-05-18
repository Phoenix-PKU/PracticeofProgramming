#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include <string>
#include "card.h"
#include "slot.h"

class Gamestate
{
private:
    std::vector<Card *> all_cards;
    int cards_clickable, cards_in_slot, cards_eliminate;
    Slot * slot;
    bool game_over;
    std::string mode;
public:
    Gamestate(int card_nums = 18, int card_types = 3);
    
    void play(void);

    bool all_cards_eliminate(void){
        return cards_clickable == 0 && cards_in_slot == 0;
    }
    
    void update(Card * card);
    
    Card * choose_one_card(void);
    
    void print_all_cards(void);
    
    void game_end(const char * status);
    
    ~Gamestate(void);
};

#endif // GAMESTATE_H
