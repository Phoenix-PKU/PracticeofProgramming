#include "confirm_box.h"
#include "ui_confirm_box.h"
#include "main_menu.h"

Confirm_Box::Confirm_Box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirm_Box)
{
    qDebug() << "Confirm_Box constructed";
    ui->setupUi(this);
}

Confirm_Box::~Confirm_Box()
{
    qDebug() << "Confirm_Box destructed";
    delete ui;
}


void Confirm_Box::on_pushButton_confirm_clicked(){
    qDebug() << "go back to main menu";
}

void Confirm_Box::on_pushButton_goback_clicked(){
    qDebug() << "go back to game";
}

