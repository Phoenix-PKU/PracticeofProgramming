#include <QPropertyAnimation>
#include <QThread>
#include "game.h"
#include "ui_game.h"
#include "menu.h"
#include "loadPic.h"
#include "ConfirmBox.h"
#include "GameOverBox.h"

class Slot;
Game::Game(int _card_num, int _card_types,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    card_nums(_card_num),
    card_types(_card_types)
{
    qDebug() << "Game constructed";
    const char * pic_dir = "../../../../sheep_and_sheep/pictures"
                            "/background_picture/grassland.jpg";
    setup_background(ui, this, "羊了个羊游戏", pic_dir, 500, 350);
    
    slot = new Slot(this);
    for (int idx = 0; idx < card_nums; ++idx) {
        Card * new_card = new Card(card_name[idx % card_types], 
            CARD_SIZE * 2 * (idx % TRIPLE), 
        CARD_SIZE * 2 + CARD_SIZE * 2 *((idx / TRIPLE) % TRIPLE), this);
        all_cards.push_back(new_card);
        connect(new_card, &QPushButton::clicked,
                this, [=](){update(new_card);});
    }
    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
}

Game::~Game()
{
    qDebug() << "Game destructed";
    delete ui;
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        delete card;
    }
    all_cards.clear();
    delete slot;
}

void Game::on_confirmBox_clicked(){
    qDebug() << "Are you sure to quit";
    ConfirmBox confirmbox;
    if(confirmbox.exec()==ConfirmBox::Accepted){
        accept();
    }
}

void Game::update(Card * chosen){
    qDebug() << "------\nA card is clicked\n------";
    cards_clickable --;
    cards_in_slot ++;

    std::vector<Card *>::iterator place = slot->find_slot(chosen);
    int where_to_go = place - slot->begin();
    slot->insert_card(chosen, place);
/*
    QPropertyAnimation * animation = new QPropertyAnimation(chosen, "geometry");
    connect(animation, &QPropertyAnimation::finished,
            this, [=](){update_tail();});
    animation->setDuration(100);
    animation->setStartValue(chosen->geometry());
    animation->setEndValue(QRect(YPOS, 50 * where_to_go, 50, 50));
    animation->start();
*/
}

void Game::update_tail() {
    if (slot->can_remove()){
        std::vector<Card *>::iterator to_remove = slot->check_slot();
        cards_in_slot -= TRIPLE;
        cards_eliminate += TRIPLE;
        slot->remove_cards(to_remove, all_cards_eliminate());
        qDebug() << "Removing three cards\n";

    }

    slot->print_slot();

    if(slot->slot_full()) {
        qDebug() << "The slot is full. You failed!!!";
        GameOverBox GameOverBox("fail");
        if((GameOverBox.exec()==ConfirmBox::Accepted)){
            accept();
        }
    }

    if(all_cards_eliminate()) {
        qDebug() << "Eliminate all cards, Congrats!!!";
        GameOverBox GameOverBox("win");
        if((GameOverBox.exec()==ConfirmBox::Accepted)){
            accept();
        }
    }

}


/*
void Game::receive_sig_choose(int target) {
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if (card->check_card_type(ClickableCard)){
            qDebug() << "--------\nA card is successfully choosed\n--------";

            std::vector<Card *>::iterator place = slot->find_slot(card);
            slot->insert_card(card, place);

            if (slot->can_remove()){
                std::vector<Card *>::iterator to_remove = slot->check_slot();
                slot->remove_cards(to_remove);
                emit sig_remove();
            }

            slot->print_slot();
            return;
        }
    }
}*/
