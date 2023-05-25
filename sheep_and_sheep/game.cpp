#include <QPropertyAnimation>
#include <QThread>
#include "game.h"
#include "ui_game.h"
#include "menu.h"
#include "ConfirmBox.h"
#include "GameOverBox.h"

Game::Game(int _card_num, int _card_types,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    card_nums(_card_num),
    card_types(_card_types)
{
    qDebug() << "Game constructed";
    ui->setupUi(this);
    this->setFixedSize(500, 350); //设置窗体固定大小
    this->setWindowTitle("羊了个羊游戏"); //到之后这里使用传入的难度
    QPixmap Images("../../../../sheep_and_sheep/pictures/background_picture/grassland.jpg");
    QPalette Palette = this->palette();
    Images = Images.scaled(this->size());
    Palette.setBrush(QPalette::Window, Images);
    setPalette(Palette);
    slot = new Slot;
    for (int i = 0; i < card_nums; ++i) {
        Card * new_card = new Card(card_name[i % card_types], 100*(i%3), 100 + 100*((i/3)%3), this);
        all_cards.push_back(new_card);
        connect(new_card, &QPushButton::clicked,
                this, [=](){update(new_card);});
    }
    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
    /*
    Gamestate * game = new Gamestate(card_nums, 3);
    connect(game, SIGNAL(sig_choose(int)), this, SLOT(receive_sig_choose(int)));
    connect(this, SIGNAL(sig_remove()), game, SLOT(receive_sig_remove()));
    game->start();
    */

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
   // else if(ConfirmBox.exec()==ConfirmBox::Rejected) {
     //   qDebug() << "not quiting\n";
   // }
}

void Game::update(Card * chosen){
    qDebug() << "------\nA card is clicked\n------";
    cards_clickable --;
    cards_in_slot ++;

    std::vector<Card *>::iterator place = slot->find_slot(chosen);
    int where_to_go = place - slot->begin();
    slot->insert_card(chosen, place);

    qDebug() << "This card goes to position " << where_to_go;

    QPropertyAnimation * animation = new QPropertyAnimation(chosen, "geometry");
    connect(animation, &QPropertyAnimation::finished,
            this, [=](){update_tail();});
    animation->setDuration(100);
    animation->setStartValue(chosen->geometry());
    animation->setEndValue(QRect(YPOS, 50 * where_to_go, 50, 50));
    animation->start();
}

void Game::update_tail() {
    if (slot->can_remove()){
        std::vector<Card *>::iterator to_remove = slot->check_slot();
        slot->remove_cards(to_remove);
        cards_in_slot -= TRIPLE;
        cards_eliminate += TRIPLE;
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
