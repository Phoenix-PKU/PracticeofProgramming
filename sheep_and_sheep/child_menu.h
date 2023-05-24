#ifndef Child_Menu_H
#define Child_Menu_H

#include <QDialog>
#include <vector>
#include "main_menu.h"
#include "card.h"
#include "slot.h"

namespace Ui {
class Child_Menu;
}

class Child_Menu : public QDialog
{
    Q_OBJECT
    int index;
    Main_Menu *p;
    Ui::Child_Menu * ui;
    std::vector<Card *> all_cards;
    Slot * slot;
    int cards_clickable, cards_in_slot, cards_eliminate;
    int card_nums, card_types;

public:
    explicit Child_Menu(int i,QWidget *parent = 0);
    ~Child_Menu();

public slots:
    void on_pushButton_clicked();
    void on_card_clicked(Card * chosen);
    void on_moving_finished();
    //void receive_sig_choose(int target);

signals:
    void sig_remove();
};

#endif // Child_Menu_H
