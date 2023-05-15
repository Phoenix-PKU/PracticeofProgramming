#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>

/*
There are three types of cards.
One type can be clicked on the main interface and
will appear in the slot when clicked.
When the card is in the slot, it will be eliminated.
*/

enum CardType {
    ClickableCard,
    SlotCard,
    EliminatedCard
};

class Card
{
private:
    int pos_x, pos_y;               /* position */
    enum CardType type;             /* status */
    std::vector<Card *> covering;        /* Cards that it covers */
    std::vector<Card *> covered;         /* Cards that covers this card */
    std::string uid;

public:
    Card(void);
    ~Card(void);
};

#endif // CARD_H
