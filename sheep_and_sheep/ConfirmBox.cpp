#include "ConfirmBox.h"
#include "ui_ConfirmBox.h"
#include "menu.h"
#include "loadPic.h"



ConfirmBox::ConfirmBox(const char * _type,
                       QDialog * _lastpage, QWidget *parent) :
    type(_type),
    lastpage(_lastpage),
    QDialog(parent),
    ui(new Ui::ConfirmBox)
{
    // qDebug() << "ConfirmBox constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/confirm.jpg";
    setup_background(ui, this, "您确认要退出吗？🧐", pic_dir, 450, 400);


    ui->confirm->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/pictures/confirm/break.png);}");
    ui->goback->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/pictures/confirm/continue.png);}");


    if(strcmp(type, "game") == 0){
        ui->bgmSlider->setValue(((Game *)lastpage)->bgm->volume() * BGM_SLIDER_RATIO);
        ui->clickSlider->setValue(((Game *)lastpage)->click->volume() * CLICK_SLIDER_RATIO);
    }
    else{
        ui->bgmSlider->setValue(((Menu *)lastpage)->bgm_menu->volume() * MENUBGM_SLIDER_RATIO);
        ui->clickSlider->setValue(((Menu *)lastpage)->click_menu->volume() * CLICK_SLIDER_RATIO);
    }
    connect(ui->bgmSlider, SIGNAL(valueChanged(int)),
            lastpage, SLOT(setBgmVolume(int)));
    connect(ui->clickSlider, SIGNAL(valueChanged(int)),
            lastpage, SLOT(setClickVolume(int)));

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

