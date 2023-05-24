#include "gameover_menu.h"
#include "ui_gameover_menu.h"
#include "main_menu.h"
#include <string>
#include <QPropertyAnimation>

Gameover_Menu::Gameover_Menu(const char * status, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gameover_Menu)
{
    qDebug() << "Gameover_Menu constructed";
    ui->setupUi(this);

    this->setWindowTitle("游戏结束！");
    QString mysource,mystatus;
    mystatus=(QString)(status);
    mysource="../../../../sheep_and_sheep/pictures/gameover/"+mystatus+".jpg";
    //qDebug() << source;
    QPixmap pix;
    bool ret=pix.load(mysource);//加载图片
    pix= pix.scaled(this->size());//改变图片大小
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    QPalette Palette = this->palette();
    pix = pix.scaled(this->size());
    Palette.setBrush(QPalette::Window, pix);
    setPalette(Palette);
}

Gameover_Menu::~Gameover_Menu()
{
    qDebug() << "Gameover_Menu destructed"; 
    delete ui;
}


void Gameover_Menu::on_pushButton_confirm_clicked(){
    qDebug() << "go back to main menu";
}

