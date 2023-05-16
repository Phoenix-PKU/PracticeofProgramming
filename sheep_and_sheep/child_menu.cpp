#include "child_menu.h"
#include "ui_child_menu.h"
#include "gamestate.h"
#include "main_menu.h"
#include "confirm_box.h"

Child_Menu::Child_Menu(int i,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Child_Menu)
{
    index=i;
    //p=parent;
    printf("child_menu constructed\n");
    ui->setupUi(this);
    Gamestate game(index*5);
}

Child_Menu::~Child_Menu()
{
    printf("child_menu destructed\n");
    delete ui;
}


void Child_Menu::on_pushButton_clicked(){
    printf("Are you sure to quit\n");
    Confirm_Box confirm_box;
    if((confirm_box.exec()==Confirm_Box::Accepted)){
        accept();
    }
}
