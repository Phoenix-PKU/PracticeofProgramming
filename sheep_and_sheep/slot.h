#ifndef SLOT_H
#define SLOT_H
#include "card.h"
#include <vector>


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

    void remove_cards(Card * start);

    void insert_card(Card * card, std::vector<Card *>::iterator place);
};

#endif // SLOT_H
