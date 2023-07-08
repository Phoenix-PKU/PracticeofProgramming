#include "ConfirmBox.h"
#include "ui_ConfirmBox.h"
#include "menu.h"
#include "loadPic.h"



ConfirmBox::ConfirmBox(Game * _game, QWidget *parent) :
    game(_game),
    QDialog(parent),
    ui(new Ui::ConfirmBox)
{
    // qDebug() << "ConfirmBox constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/confirm.jpg";
    setup_background(ui, this, "您确认要退出吗？🧐", pic_dir, 450, 400);
    ui->confirm->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/pictures/confirm/break.png);}");
    ui->goback->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/pictures/confirm/continue.png);}");
    ui->bgmSlider->setValue(game->bgm->volume() * BGM_SLIDER_RATIO);
    ui->clickSlider->setValue(game->click->volume() * CLICK_SLIDER_RATIO);
    connect(ui->bgmSlider, SIGNAL(valueChanged(int)),
            game, SLOT(setBgmVolume(int)));
    connect(ui->clickSlider, SIGNAL(valueChanged(int)),
            game, SLOT(setClickVolume(int)));
}

ConfirmBox::~ConfirmBox()
{
    // qDebug() << "ConfirmBox destructed";
    delete ui;
}


void ConfirmBox::on_confirm_clicked(){
    // qDebug() << "go back to main menu";
    return ;
}

void ConfirmBox::on_goback_clicked(){
    // qDebug() << "go back to game";
    return ;
}


void ConfirmBox::on_bgmSlider_valueChanged(int value)
{
    // qDebug() << "bgm silder changed to " << value;
    // game->bgm->setVolume(value / BGM_SLIDER_RATIO);
}

void ConfirmBox::on_clickSlider_valueChanged(int value)
{

}

