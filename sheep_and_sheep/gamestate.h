#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>
#include <string>
#include "card.h"
#include "slot.h"
#include <QDialog>
#include <QThread>

class Gamestate : public QThread
{
    Q_OBJECT
private:
    int cards_clickable, cards_in_slot, cards_eliminate;
    bool game_over;
    std::string mode;
public:
    Gamestate(int card_nums = 18, int card_types = 3);

    bool slot_full(void){
        return cards_in_slot == 7;
    }
    bool all_cards_eliminate(void){
        return cards_clickable == 0 && cards_in_slot == 0;
    }
    
    void update(void);
    
    int choose_one_card(void);
    
    void print_all_cards(void);
    
    void game_end(const char * status);
    
    ~Gamestate(void);
protected:
    void run();
signals:
    void sig_choose(int target);
public slots:
    void receive_sig_remove() {cards_in_slot -= TRIPLE;    cards_eliminate += TRIPLE;};
};

#endif // GAMESTATE_H
