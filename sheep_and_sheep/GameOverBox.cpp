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
    // qDebug() << "GameOverBox constructed";
    char pic_dir[MAXLINE];
    strcpy(pic_dir, ":/new/prefix1/pictures/gameover/");
    strcpy(pic_dir + strlen(pic_dir), status);
    strcpy(pic_dir + strlen(pic_dir), ".jpg");
    const char * title;
    if (strcmp(status, "fail") == 0)
        title = "好可惜, 你差一点就羊了😭";
    else
        title = "恭喜你, 你加入了羊群!😁";
    setup_background(ui, this, title, pic_dir, 400, 200);
}

GameOverBox::~GameOverBox()
{
    // qDebug() << "GameOverBox destructed"; 
    delete ui;
}


void GameOverBox::on_goToMainMenu_clicked(){
    // qDebug() << "go back to main menu";
}

