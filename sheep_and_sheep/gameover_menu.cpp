#include "gameover_menu.h"
#include "ui_gameover_menu.h"
#include "main_menu.h"
#include <string>

Gameover_Menu::Gameover_Menu(const char * status, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gameover_Menu)
{
    qDebug() << "Gameover_Menu constructed";
    ui->setupUi(this);
    if(strcmp(status, "win") == 0)
        ui->label->setText("Eliminate all cards, Congrats!!!");
    else if(strcmp(status, "fail") == 0)
        ui->label->setText("The slot is full. You failed!!!");
}

Gameover_Menu::~Gameover_Menu()
{
    qDebug() << "Gameover_Menu destructed";
    delete ui;
}


void Gameover_Menu::on_pushButton_confirm_clicked(){
    qDebug() << "go back to main menu";
}

