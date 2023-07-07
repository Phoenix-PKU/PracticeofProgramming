#include <QPushButton>
#include <QPropertyAnimation>
#include <QThread>
#include <QGraphicsDropShadowEffect>
#include "game.h"
#include "ui_game.h"
#include "menu.h"
#include "loadPic.h"
#include "ConfirmBox.h"
#include "GameOverBox.h"
#include "progressbar.h"
#include <random>
#include "Hyperlink.h"

#define ANI_TIME    100
template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end);
/* given an idx, find the type of the card to be put in the heap. */
static int get_type(int randidx, std::vector<int> & _cards_left,int & _ncard);
static bool avail_crash(Card * card);


class Slot;
Game::Game(int _card_num, int _card_types,int _cards_in_heap,int _shuffle_left,int _retreat_left,int _crash_left, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game),
    card_nums(_card_num),
    card_types(_card_types),
    cards_in_heap(_cards_in_heap),
    shuffle_left(_shuffle_left),
    retreat_left(_retreat_left),
    crash_left(_crash_left)
{
    length = 15 * CARD_SIZE;
    width = 11 * CARD_SIZE;
    /* max number of card that can appear on one line. */
    max_num_card = 13; 
    qDebug() << "Game constructed";
    const char * pic_dir = ":/new/prefix1/pictures"
                            "/background_picture/grassland.png";
    setup_background(ui, this, "羊了个羊游戏", pic_dir, length, width);
    
    //初始化进度条
    move = new Bar("Move", 0, this);
    cover = new Bar("Cover", BAR_LEN, this);
    move->show();
    cover->show();
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(18);
    QString temp;
    temp=(QString)(std::to_string(shuffle_left)).c_str();
    ui->shuffle_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+temp);
    ui->shuffle_left_label->setFont(ft);
    ui->shuffle_left_label->setAlignment(Qt::AlignCenter);
    temp=(QString)(std::to_string(retreat_left)).c_str();
    ui->retreat_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+temp);
    ui->retreat_left_label->setFont(ft);
    ui->retreat_left_label->setAlignment(Qt::AlignCenter);
    temp=(QString)(std::to_string(crash_left)).c_str();
    ui->crash_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+temp);
    ui->crash_left_label->setFont(ft);
    ui->crash_left_label->setAlignment(Qt::AlignCenter);

    std::random_device rd;
    slot = new Slot(this);

    int idx;
    int ncard=card_nums; //剩余未放置的卡牌总数
    std::vector<int> cards_left; //剩余每个类未放置卡牌的个数
    for (int i=0;i<card_types;++i){
        cards_left.push_back(card_nums/card_types);
    }
    for (idx=0; idx < cards_in_heap-heap_show; ++idx){
        int temp=rd() % ncard;
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP1_X, HEAP1_Y,
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (; idx < cards_in_heap; ++idx){
        int temp=rd() % ncard;
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP1_X, HEAP1_Y+delta*(heap_show+1-cards_in_heap+idx),
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (idx=_cards_in_heap; idx < 2*cards_in_heap-heap_show; ++idx){
        int temp=rd() % ncard;
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP2_X, HEAP2_Y,
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (; idx < 2*cards_in_heap; ++idx){
        int temp=rd() % ncard;
        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  HEAP2_X, HEAP2_Y+delta*(heap_show+1-2*cards_in_heap+idx),
                                  all_cards, this,1);
        all_cards.push_back(new_card);
    }
    for (idx = 2 * cards_in_heap; idx < card_nums; ++idx) {

        int posx = (rd() % max_num_card + 4) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 3.5) * MCARD_SIZE;
        int temp=rd() % ncard;

        Card * new_card = new Card(card_name[get_type(temp,cards_left,ncard)],
                                  posx, posy,
                                  all_cards, this);
        all_cards.push_back(new_card);
    }

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        card->print_card(true, "");
        connect(card, &QPushButton::clicked,
                this, [=](){update(card);});
    }

    cards_clickable = card_nums;
    cards_in_slot = 0;
    cards_eliminate = 0;
    this -> consistency_check();
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
    qDebug() << "------\nCard "<< chosen->get_id() <<" is clicked\n------";

    cards_clickable --;
    cards_in_slot ++;

    cover->hide();
    move->set_len((double)BAR_LEN * (card_nums - cards_clickable)
                                    / card_nums);
    cover->show();

    chosen->remove_card();
    std::vector<Card *>::iterator place = slot->find_slot(chosen);
    int where_to_go = place - slot->begin();
    slot->insert_card(chosen, place);
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
        accept();
    }

    if(all_cards_eliminate()) {
        qDebug() << "Eliminate all cards, Congrats!!!";
        GameOverBox GameOverBox("win");
        if((GameOverBox.exec()==ConfirmBox::Accepted)){
            accept();
        }
        accept();
    }
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        (*ip)->print_card(true, "");
    }
    this -> consistency_check();
}

/* This function choose the last card in the slot and put it back 
    to clickable card. 
    It wouldn't work if there is no card in the slot.
    The card will be put back to where it belongs.
*/
void Game::on_retreat_clicked(){
    if (retreat_left <= 0){
        Hyperlink hyperlink(&retreat_left);
        hyperlink.exec();
    }
    if (retreat_left <= 0){
        return;
    }

    // check condition
    qDebug() << "retreat one card";
    if (cards_in_slot == 0) {
        qDebug() << "no card to retreat!";
        return;
    }

    //update slot
    slot->print_slot();
    Card * to_retreat = slot -> get_last_card();
    assert (to_retreat->check_card_type(SlotCard));
    slot -> remove_last_card();
    
    //update game
    cards_in_slot--;
    cards_clickable++;
    //update progressbar
    cover->hide();
    move->set_len((double)BAR_LEN * (card_nums - cards_clickable)
                  / card_nums);
    cover->show();

    //do animation
    QPropertyAnimation *animation = new QPropertyAnimation(to_retreat, "geometry");
    animation_helper(animation, ANI_TIME, to_retreat->geometry(),
            QRect(to_retreat->get_orix(), to_retreat->get_oriy(), 
            CARD_SIZE,  CARD_SIZE));
    //update card
    to_retreat->set_posx(to_retreat->get_orix());
    to_retreat->set_posy(to_retreat->get_oriy());
    to_retreat->set_card_type(ClickableCard);
    to_retreat->setNormalBackground();
    to_retreat->setEnabled(true);
    to_retreat->print_card(true, "");
    //raise it to the upmost layer
    to_retreat->raise();

    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * old_card = *ip;
        if (old_card->check_card_type(SlotCard) ||
            old_card->check_card_type(EliminatedCard))
            continue;
        if (old_card == to_retreat) continue;
        if (overlap(old_card, to_retreat)){
            cover_card(to_retreat, old_card);
        }
    }
    --retreat_left;
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(18);
    QString temp;
    temp=(QString)(std::to_string(retreat_left)).c_str();
    ui->retreat_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+temp);
    ui->retreat_left_label->setFont(ft);
    ui->retreat_left_label->setAlignment(Qt::AlignCenter);

    this->consistency_check();
}

void Game::on_myshuffle_clicked()
{
    if (shuffle_left <= 0){
        Hyperlink hyperlink(&shuffle_left);
        hyperlink.exec();
    }
    if (shuffle_left <= 0){
        return;
    }


    qDebug() << "shuffle cards";
    std::vector<Card *>::iterator card_i;
    std::vector<int>::iterator p_temp;
    std::vector<int> temp;

    // pick up all cards that is clickable or covered
    // delete them and put them into temp.

    for (card_i=all_cards.begin();card_i!=all_cards.end();){
        if ((!(*card_i)->in_heap) && ((*card_i)->check_card_type(ClickableCard)
               ||(*card_i)->check_card_type(CoveredCard))){
            temp.push_back((*card_i)->nametoint());
            delete (*card_i);
            card_i=all_cards.erase(card_i);
        }
        else{
            ++card_i;
        }
    }

    // create new cards that has random position

    std::random_device rd;
    for (p_temp=temp.begin();p_temp!=temp.end();++p_temp){
        int posx = (rd() % max_num_card + 4) * MCARD_SIZE;
        int posy = (rd() % max_num_card + 3.5) * MCARD_SIZE;
        Card * new_card = new Card(card_name[*p_temp],
                                  posx, posy,
                                  all_cards, this);
        connect(new_card, &QPushButton::clicked, this, 
                [=](){update(new_card);});
        all_cards.push_back(new_card);
    }

    // set background and enable of new cards.
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        if(card -> check_card_type(ClickableCard)){
            card->setNormalBackground();
            card->setEnabled(true);
        }
        else if(card -> check_card_type(CoveredCard)){
            card->setDarkBackground();
            card->setEnabled(false);
        }
    }

    --shuffle_left;
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(18);
    ui->shuffle_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+
                                    (QString)(std::to_string(shuffle_left)).c_str());
    ui->shuffle_left_label->setFont(ft);
    ui->shuffle_left_label->setAlignment(Qt::AlignCenter);

    this->consistency_check();

}



void Game::on_crash_clicked(){
    if (crash_left <= 0){
        Hyperlink hyperlink(&crash_left);
        hyperlink.exec();
    }
    if (crash_left <= 0){
        return;
    }


    qDebug() << "Crash clicked";
    // find three cards in cards_clickable;
    bool flag = false;
    Card * card1 = NULL, * card2 = NULL, * card3 = NULL;
    for (int i = 0;i < card_nums;i ++){
        card1 = all_cards[i];
        if (!avail_crash(card1)) continue;

        for (int j = i + 1;j < card_nums;j ++){
            card2 = all_cards[j];
            if (!avail_crash(card2)) continue;
            if (strcmp(card2->name, card1->name) != 0) continue;

            for (int k = j + 1;k < card_nums;k ++){
                card3 = all_cards[k];
                if (!avail_crash(card3)) continue;
                if (strcmp(card3->name, card1->name) != 0) continue;
                flag = true; break;
            }
            if (flag) break;
        }
        if (flag) break;
    }
    if (!flag) {
        qDebug() << "no cards to crash";
        return ;
    }

    else{
        // card update
        card1->crash_card();
        card2->crash_card();
        card3->crash_card();
        cards_clickable -= 3;
        cards_eliminate += 3;
        // progress bar update
        cover->hide();
        move->set_len((double)BAR_LEN * (card_nums - cards_clickable)
                  / card_nums);
        cover->show();
        // possible win!
        if(all_cards_eliminate()) {
            qDebug() << "Eliminate all cards, Congrats!!!";
            GameOverBox GameOverBox("win");
            if((GameOverBox.exec()==ConfirmBox::Accepted)){
                accept();
            }
            accept();
        }
    }
    --crash_left;
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(18);
    ui->crash_left_label->setText("<a style='color: white; text-decoration: bold'=lately>"+
                                  (QString)(std::to_string(crash_left)).c_str());
    ui->crash_left_label->setFont(ft);
    ui->crash_left_label->setAlignment(Qt::AlignCenter);

    this -> consistency_check();


}

template <class Amt, class Pos1, class Pos2>
static void animation_helper(Amt * ani, int dur, Pos1 start, Pos2 end){
    ani->setDuration(dur);
    ani->setStartValue(start);
    ani->setEndValue(end);
    ani->start();
}

void Game::consistency_check(void){
    slot -> slot_concheck(cards_in_slot);
    std::vector<int> cards; cards.resize(card_types);
    for (int i = 0;i < card_types;i ++) cards[i] = 0;
    int real_clickable = 0, real_in_slot = 0, real_eliminate = 0;
    for (auto ip = all_cards.begin();ip != all_cards.end();ip ++){
        Card * card = *ip;
        cards[card->nametoint()] += 1;
        card -> cardconcheck();
        if (card->check_card_type(ClickableCard) || card->check_card_type(CoveredCard))
            real_clickable ++;
        else if (card->check_card_type(SlotCard)){
            real_in_slot ++;
        }
        else if (card->check_card_type(EliminatedCard)){
            real_eliminate ++;
        }
    }
    for (int i = 0;i < card_types;i ++){
        assert (cards[i] == card_nums / card_types);
    }

    assert (real_clickable == cards_clickable);
    assert (real_in_slot == cards_in_slot);
    assert (real_eliminate == cards_eliminate);
    assert (real_clickable + real_in_slot + real_eliminate == card_nums);
}


static int get_type(int randidx, std::vector<int> & _cards_left,int & _ncard){
    int temp=randidx,n=0;
    for(std::vector<int>::iterator p = _cards_left.begin();p!=_cards_left.end();++p){
        n+=*p;
        if (temp < n){
            (*p)--;
            --_ncard;
            return p-_cards_left.begin();
        }
    }
    assert (false);
}

static bool avail_crash(Card * card){
    if (card->check_card_type(EliminatedCard) || 
        card->check_card_type(SlotCard) || 
        card->in_heap){
        return false;
    }
    else{
        return true;
    }
}


