#include "confirm_box.h"
#include "ui_confirm_box.h"
#include "gamestate.h"
#include "main_menu.h"

Confirm_Box::Confirm_Box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirm_Box)
{
    printf("Confirm_Box constructed\n");
    ui->setupUi(this);
}

Confirm_Box::~Confirm_Box()
{
    printf("Confirm_Box destructed\n");
    delete ui;
}


void Confirm_Box::on_pushButton_confirm_clicked(){
    printf("go back to main menu\n");
}

void Confirm_Box::on_pushButton_goback_clicked(){
    printf("go back to game\n");
}

