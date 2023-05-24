#include "main_menu.h"
#include "ui_main_menu.h"
#include "child_menu.h"

Main_Menu::Main_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    qDebug() << "main menu constructed";
    ui->setupUi(this);
}

Main_Menu::~Main_Menu()
{
    qDebug() << "main menu destructed";
    delete ui;
}

void Main_Menu::on_pushButton_clicked()
{
    qDebug() << "quit game";
    rejected();
    //也可以通过 按F4进入信号和槽编辑状态，拖动 pushButton到对话框窗体，
    //然后添加 clicked() - accept槽
    //MyWidget w;
    //w.show();
}

void Main_Menu::on_pushButton_easy_clicked()
{
    qDebug() << "start easy game";
    Child_Menu dlg(1);
    qDebug() << "child menu loaded";
    dlg.exec();
}
void Main_Menu::on_pushButton_medium_clicked()
{
    qDebug() << "start medium game";
    Child_Menu dlg(2);
    dlg.exec();
}
void Main_Menu::on_pushButton_hard_clicked()
{
    qDebug() << "start hard game";
    Child_Menu dlg(3);
    dlg.exec();
}
void Main_Menu::on_pushButton_hell_clicked()
{
    qDebug() << "start hell game";
    Child_Menu dlg(4);
    dlg.exec();
}
