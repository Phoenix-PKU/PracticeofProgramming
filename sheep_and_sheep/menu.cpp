#include "menu.h"
#include "ui_menu.h"
#include "ConfirmBox.h"
#include "game.h"
#include "loadPic.h"

#define MANY    1 << 30

struct GameParameters
{
    int cardNum;
    int cardType;
    int cardInHeap;
    int numShuffle;
    int numRetreat;
    int numCrash;
};

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    // qDebug() << "main menu constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/main_menu.jpg";
    setup_background(ui, this, "欢迎来到羊了个羊的世界💕🥰", pic_dir, 500, 400);
    //ui->hard->setStyleSheet("background-color: rgba(255, 255, 255, 80)");
}

Menu::~Menu()
{
    // qDebug() << "main menu destructed";
    delete ui;
}

void Menu::on_quit_clicked()
{
    // qDebug() << "quit game";
    ConfirmBox confirmbox(0);
    if (confirmbox.exec() == ConfirmBox::Accepted){
        accept();
    }
}

void Menu::on_easy_clicked()
{
    // qDebug() << "start easy game";
    GameParameters params{18, 3, 0, 0, 0, 0};
    startGame(params);
}

void Menu::on_medium_clicked()
{
    // qDebug() << "start medium game";
    GameParameters params{63, 7, 4, 1, 1, 1};
    startGame(params);
}

void Menu::on_hard_clicked()
{
    // qDebug() << "start hard game";
    GameParameters params{198, 11, 8, 1, 1, 1};
    startGame(params);
}

void Menu::on_hell_clicked()
{
    // qDebug() << "start hell game";
    GameParameters params{405, 15, 12, 2, 2, 2};
    startGame(params);
}

void Menu::startGame(const GameParameters& params)
{
    Game game(params.cardNum, params.cardType, params.cardInHeap,
              params.numShuffle, params.numRetreat, params.numCrash);
    game.exec();
}
