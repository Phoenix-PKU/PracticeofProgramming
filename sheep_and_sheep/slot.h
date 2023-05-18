#ifndef SLOT_H
#define SLOT_H
#include "card.h"
#include <vector>

#define TRIPLE 3

class Slot
{
private:
    int size;           /* max size of slot */
    int curr_size;      /* current size of slot */
    std::vector<Card *> cards;   /* All cards in slot */
public:
    Slot(int max_size = 7);

    ~Slot(void);

    std::vector<Card *>::iterator find_slot(Card * card);

    std::vector<Card *>::iterator check_slot(void);

    bool can_remove(void);

    void remove_cards(std::vector<Card *>::iterator card_it);

    void insert_card(Card * card, std::vector<Card *>::iterator place);

    void print_slot(void);

    bool slot_full(void){
        return curr_size == size;
    }
};

#endif // SLOT_H
