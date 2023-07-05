#ifndef SLOT_H
#define SLOT_H
#include "card.h"
#include "game.h"
#include <vector>

#define TRIPLE 3

#define YPOS 400
class Game;
class Slot
{
private:
    int size;           /* max size of slot */
    int curr_size;      /* current size of slot */
    Game * game;
    std::vector<Card *> cards;   /* All cards in slot */
public:
    Slot(Game * _game, int max_size = 7);

    ~Slot(void);

    std::vector<Card *>::iterator begin(void) {return cards.begin();}

    std::vector<Card *>::iterator find_slot(Card * card);

    std::vector<Card *>::iterator check_slot(void);

    bool can_remove(void);

    Card * get_last_card(void);

    void remove_last_card(void);

    void remove_cards(std::vector<Card *>::iterator card_it, bool win);

    void insert_card(Card * card, std::vector<Card *>::iterator place);

    void print_slot(void);

    bool slot_full(void){
        return curr_size == size;
    }
};

#endif // SLOT_H
