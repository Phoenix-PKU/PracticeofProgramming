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
    setup_background(ui, this, "欢迎来到🐏了个🐑的世界💕🥰", pic_dir, 500, 400);

    bgm_menu = new QSoundEffect(this);
    bgm_menu->setSource(QUrl::fromLocalFile(":/new/prefix1/sounds/bgm_menu.wav"));
    bgm_menu->setLoopCount(QSoundEffect::Infinite);
    bgm_menu->setVolume(50 / MENUBGM_SLIDER_RATIO);
    bgm_menu->play();

    click_menu = new QSoundEffect(this);
    click_menu->setSource(QUrl::fromLocalFile(":/new/prefix1/sounds/click.wav"));
    click_menu->setVolume(50 / CLICK_SLIDER_RATIO);
}

Menu::~Menu()
{
    // qDebug() << "main menu destructed";
    delete ui;
    delete bgm_menu;
    delete click_menu;
}

void Menu::on_quit_clicked()
{
    // qDebug() << "quit game";
    click_menu->play();
    ConfirmBox confirmbox("menu", this);
    if (confirmbox.exec() == ConfirmBox::Accepted){
        accept();
    }
}

void Menu::on_easy_clicked()
{
    // qDebug() << "start easy game";
    click_menu->play();
    GameParameters params{18, 3, 0, 0, 0, 0};
    startGame(params);
}

void Menu::on_medium_clicked()
{
    // qDebug() << "start medium game";
    click_menu->play();
    GameParameters params{63, 7, 4, 1, 1, 1};
    startGame(params);
}

void Menu::on_hard_clicked()
{
    // qDebug() << "start hard game";
    click_menu->play();
    GameParameters params{198, 11, 8, 1, 1, 1};
    startGame(params);
}

void Menu::on_hell_clicked()
{
    // qDebug() << "start hell game";
    click_menu->play();
    GameParameters params{405, 15, 12, 2, 2, 2};
    startGame(params);
}

void Menu::startGame(const GameParameters& params)
{
    Game game(params.cardNum, params.cardType, params.cardInHeap,
              params.numShuffle, params.numRetreat, params.numCrash);
    game.exec();
}

void Menu::setBgmVolume(int value){
    bgm_menu->setVolume(value / MENUBGM_SLIDER_RATIO);
}

void Menu::setClickVolume(int value){
    click_menu->setVolume(value / CLICK_SLIDER_RATIO);
}
