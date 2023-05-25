#include "GameOverBox.h"
#include "ui_GameOverBox.h"
#include "menu.h"
#include <string>
#include <QPropertyAnimation>

GameOverBox::GameOverBox(const char * status, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverBox)
{
    qDebug() << "GameOverBox constructed";
    ui->setupUi(this);

    this->setWindowTitle("游戏结束！");
    QString mysource,mystatus;
    mystatus=(QString)(status);
    mysource="../../../../sheep_and_sheep/pictures/gameover/"+mystatus+".jpg";
    //qDebug() << source;
    QPixmap pix;
    bool ret=pix.load(mysource);//加载图片
    pix= pix.scaled(this->size());//改变图片大小
    QPalette Palette = this->palette();
    pix = pix.scaled(this->size());
    Palette.setBrush(QPalette::Window, pix);
    setPalette(Palette);
}

GameOverBox::~GameOverBox()
{
    qDebug() << "GameOverBox destructed"; 
    delete ui;
}


void GameOverBox::on_goToMainMenu_clicked(){
    qDebug() << "go back to main menu";
    //accept();
}

