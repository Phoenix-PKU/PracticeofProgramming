#include "main_menu.h"
#include "ui_main_menu.h"
#include "child_menu.h"

Main_Menu::Main_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    printf("main menu constructed\n");
    ui->setupUi(this);
}

Main_Menu::~Main_Menu()
{
    printf("main menu destructed\n");
    delete ui;
}

void Main_Menu::on_pushButton_clicked()
{
    printf("quit game\n");
    rejected();
    //也可以通过 按F4进入信号和槽编辑状态，拖动 pushButton到对话框窗体，
    //然后添加 clicked() - accept槽
    //MyWidget w;
    //w.show();
}

void Main_Menu::on_pushButton_easy_clicked()
{
    printf("start easy game\n");
    Child_Menu dlg(1);
    dlg.exec();
}
void Main_Menu::on_pushButton_medium_clicked()
{
    printf("start medium game\n");
    Child_Menu dlg(2);
    dlg.exec();
}
void Main_Menu::on_pushButton_hard_clicked()
{
    printf("start hard game\n");
    Child_Menu dlg(3);
    dlg.exec();
}
void Main_Menu::on_pushButton_hell_clicked()
{
    printf("start hell game\n");
    Child_Menu dlg(4);
    dlg.exec();
}
