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
    Slot * slot;
    bool game_over;
    std::string mode;
public:
    Gamestate(int card_nums = 9);
    void play();
    ~Gamestate();
};

#endif // GAMESTATE_H
