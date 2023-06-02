#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include <QWidget>
#include <QDialog>
#include <QPushButton>

#define CARD_SIZE   54
#define HCARD_SIZE  CARD_SIZE / 2
#define DCARD_SIZE  CARD_SIZE * 2
#define TCARD_SIZE  CARD_SIZE * 3
#define MIN_OVERLAP_RATIO   2
#define MCARD_SIZE  CARD_SIZE / MIN_OVERLAP_RATIO


extern const int max_type_of_cards;
extern const char* card_name[];
extern const int current_type_of_cards;
class Game;
/*
There are three types of cards.
One type can be clicked on the main interface and
will appear in the slot when clicked.
When the card is in the slot, it will be eliminated.
*/

enum CardType {
    ClickableCard,
    CoveredCard,
    SlotCard,
    EliminatedCard
};

class Card:public QPushButton
{
    Q_OBJECT
private:
    static unsigned long long ID;
    int posx, posy, orix, oriy;               /* position */
    enum CardType type;             /* status */
    std::vector<Card *> covering;        /* Cards that it covers */
    std::vector<Card *> covered;         /* Cards that covers this card */
    std::string uid;                /* uid. */
    Game * game;
public:
    const char * name;
    bool check_card_type(enum CardType _type){
        return type == _type;
    }
    void set_card_type(enum CardType _type){
        type = _type;
    }
    
    const char * get_id(void){
        return uid.c_str();
    }

    void print_card(bool cover_flag, const char * prefix);

    void remove_card(void);

    void remove_upper_card(Card * upper_card);

    void set_upper_card(Card * upper_card);

    Card(const char * _name, int _posx, int _posy,
    const std::vector<Card *> all_cards, QDialog * parent);

    ~Card(void);

    friend void cover_card(Card * upper_card, Card * lower);

    friend bool overlap(Card * old_card, Card * new_card);

protected:
    //void mousePressEvent(QMouseEvent * e);

};
void cover_card(Card * upper_card, Card * lower_card);
bool overlap(Card * old_card, Card * new_card);
#endif // CARD_H
