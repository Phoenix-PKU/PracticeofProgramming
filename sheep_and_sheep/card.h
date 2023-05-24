#ifndef CARD_H
#define CARD_H

#include <vector>
#include <string>
#include <QWidget>
#include <QDialog>
#include <QPushButton>
extern const int max_type_of_cards;
extern const char* card_name[];
extern const int current_type_of_cards;

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

class Card:public QPushButton
{
    Q_OBJECT
private:
    static unsigned long long lxid;
    int pos_x, pos_y;               /* position */
    enum CardType type;             /* status */
    std::vector<Card *> covering;        /* Cards that it covers */
    std::vector<Card *> covered;         /* Cards that covers this card */
    std::string uid;                /* uid. */

public:
    const char * name;
    bool check_card_type(enum CardType _type){
        return type == _type;
    }
    void set_card_type(enum CardType _type){
        type = _type;
    }
    void print_card(void);
    Card(const char * _name, int posx, int posy, QDialog * parent);

    ~Card(void);

protected:
    //void mousePressEvent(QMouseEvent * e);

};

#endif // CARD_H
