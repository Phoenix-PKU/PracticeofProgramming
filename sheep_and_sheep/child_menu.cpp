#include <QPropertyAnimation>
#include <QThread>
#include "child_menu.h"
#include "ui_child_menu.h"
#include "main_menu.h"
#include "confirm_box.h"
#include "gameover_menu.h"

Child_Menu::Child_Menu(int i,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Child_Menu),
    index(i)
{
    qDebug() << "child_menu constructed";
    ui->setupUi(this);
    this->setFixedSize(500, 350); //设置窗体固定大小

    this->setWindowTitle("羊了个羊游戏"); //到之后这里使用传入的难度
    QPixmap Images("../../../../sheep_and_sheep/pictures/background_picture/grassland.jpg");
    QPalette Palette = this->palette();
    Images = Images.scaled(this->size());
    Palette.setBrush(QPalette::Window, Images);
    setPalette(Palette);
    card_nums = 6 * i + 12;
    card_types = i + 2;
    slot = new Slot;
    for (int i = 0; i < card_nums; ++i) {
        Card * new_card = new Card(card_name[i % card_types], 100*(i%3), 100 + 100*((i/3)%3), this);
        all_cards.push_back(new_card);
        connect(new_card, &QPushButton::clicked,
                this, [=](){on_card_clicked(new_card);});
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

Child_Menu::~Child_Menu()
{
    qDebug() << "child_menu destructed";
    delete ui;
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        delete card;
    }
    all_cards.clear();
    delete slot;
}


void Child_Menu::on_pushButton_clicked(){
    qDebug() << "Are you sure to quit";
    Confirm_Box confirm_box;
    if((confirm_box.exec()==Confirm_Box::Accepted)){
        accept();
    }
}

void Child_Menu::on_card_clicked(Card * chosen){
    qDebug() << "------\nA card is clicked\n------";
    cards_clickable --;
    cards_in_slot ++;

    std::vector<Card *>::iterator place = slot->find_slot(chosen);
    int where_to_go = place - slot->begin();
    slot->insert_card(chosen, place);

    qDebug() << "This card goes to position " << where_to_go;

    QPropertyAnimation * animation = new QPropertyAnimation(chosen, "geometry");
    connect(animation, &QPropertyAnimation::finished,
            this, [=](){on_moving_finished();});
    animation->setDuration(100);
    animation->setStartValue(chosen->geometry());
    animation->setEndValue(QRect(YPOS, 50 * where_to_go, 50, 50));
    animation->start();
}

void Child_Menu::on_moving_finished() {
    if (slot->can_remove()){
        std::vector<Card *>::iterator to_remove = slot->check_slot();
        slot->remove_cards(to_remove);
        cards_in_slot -= TRIPLE;
        cards_eliminate += TRIPLE;
    }

    slot->print_slot();

    if(slot->slot_full()) {
        qDebug() << "The slot is full. You failed!!!";
        Gameover_Menu gameover_menu("fail");
        if((gameover_menu.exec()==Confirm_Box::Accepted)){
            accept();
        }
    }

    if(cards_clickable == 0 && cards_in_slot == 0) {
        qDebug() << "Eliminate all cards, Congrats!!!";
        Gameover_Menu gameover_menu("win");
        if((gameover_menu.exec()==Confirm_Box::Accepted)){
            accept();
        }
    }

}
/*
void Child_Menu::receive_sig_choose(int target) {
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
