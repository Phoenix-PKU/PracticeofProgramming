#include "ConfirmBox.h"
#include "ui_ConfirmBox.h"
#include "menu.h"
#include "loadPic.h"

ConfirmBox::ConfirmBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmBox)
{
    qDebug() << "ConfirmBox constructed";
    const char * pic_dir = ":/new/prefix1/pictures/background_picture/warning.jpg";
    setup_background(ui, this, "您确认要退出吗？", pic_dir, 240, 100);
}

ConfirmBox::~ConfirmBox()
{
    qDebug() << "ConfirmBox destructed";
    delete ui;
}


void ConfirmBox::on_confirm_clicked(){
    qDebug() << "go back to main menu";
}

void ConfirmBox::on_goback_clicked(){
    qDebug() << "go back to game";
}

