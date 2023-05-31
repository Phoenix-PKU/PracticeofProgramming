#include "menu.h"
#include "ui_menu.h"
#include "ConfirmBox.h"
#include "game.h"
#include "loadPic.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    qDebug() << "main menu constructed";
    const char * pic_dir = "../../../../sheep_and_sheep/pictures/background_picture/main_menu.jpg";
    setup_background(ui, this, "欢迎来到羊了个羊的世界", pic_dir, 400, 300);
}

Menu::~Menu()
{
    qDebug() << "main menu destructed";
    delete ui;
}

void Menu::on_quit_clicked()
{
    qDebug() << "quit game";
    ConfirmBox confirmbox;
    if (confirmbox.exec() == ConfirmBox::Accepted){
        accept();
    }
}

void Menu::on_easy_clicked()
{
    qDebug() << "start easy game";
    Game game(18, 3);
    game.exec();
}
void Menu::on_medium_clicked()
{
    qDebug() << "start medium game";
    Game game(24, 4);
    game.exec();
}
void Menu::on_hard_clicked()
{
    qDebug() << "start hard game";
    Game game(30, 5);
    game.exec();
}
void Menu::on_hell_clicked()
{
    qDebug() << "start hell game";
    Game game(36, 6);
    game.exec();
}
