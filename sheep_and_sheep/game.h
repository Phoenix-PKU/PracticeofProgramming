#ifndef Game_H
#define Game_H

#include <QDialog>
#include <QtMultimedia/QSoundEffect>
#include <vector>
#include "menu.h"
#include "card.h"
#include "slot.h"
#include "progressbar.h"
class Slot;
namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT
    int index;
    Menu *p;
    Ui::Game * ui;
    std::vector<Card *> all_cards;
    Slot * slot;
    Bar * move, * cover;
    int cards_clickable, cards_in_slot, cards_eliminate;
    int card_nums, card_types, cards_in_heap;
    int length, width, max_num_card;
    int shuffle_left,retreat_left,crash_left;
    QSoundEffect * bgm;
    QSoundEffect * bingo;
    QSoundEffect * click;
public:
    explicit Game(int _card_nums, int _card_types ,int _cards_in_heap,int _shuffle_left, int _retreat_left,int _crash_left, QWidget *parent = 0);
    ~Game();

public slots:
    void on_confirmBox_clicked(void);
    void on_retreat_clicked(void);
    void on_crash_clicked(void);
    void update(Card * chosen);
    void update_tail(void);
    bool all_cards_eliminate(void){
         return cards_clickable == 0 && cards_in_slot == 0;
     }
    void on_myshuffle_clicked();
    void consistency_check(void);

signals:
    void sig_remove();
};

#endif // Game_H
