#include <string>
#include <string.h>
#include <QPropertyAnimation>

#include "GameOverBox.h"
#include "ui_GameOverBox.h"
#include "menu.h"
#include "loadPic.h"

#define MAXLINE 128

GameOverBox::GameOverBox(const char * status, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverBox)
{
    qDebug() << "GameOverBox constructed";
    char pic_dir[MAXLINE];
    strcpy(pic_dir, "../sheep_and_sheep/pictures/gameover/");
    strcpy(pic_dir + strlen(pic_dir), status);
    strcpy(pic_dir + strlen(pic_dir), ".jpg");
    setup_background(ui, this, "GAMEOVER!", pic_dir);
}

GameOverBox::~GameOverBox()
{
    qDebug() << "GameOverBox destructed"; 
    delete ui;
}


void GameOverBox::on_goToMainMenu_clicked(){
    qDebug() << "go back to main menu";
}

