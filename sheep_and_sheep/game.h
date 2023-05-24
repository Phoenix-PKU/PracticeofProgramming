#ifndef Game_H
#define Game_H

#include <QDialog>
#include <vector>
#include "menu.h"
#include "card.h"
#include "slot.h"

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
    int cards_clickable, cards_in_slot, cards_eliminate;
    int card_nums, card_types;

public:
    explicit Game(int i,QWidget *parent = 0);
    ~Game();

public slots:
    void on_pushButton_clicked();
    void on_card_clicked(Card * chosen);
    void on_moving_finished();
    //void receive_sig_choose(int target);

signals:
    void sig_remove();
};

#endif // Game_H
