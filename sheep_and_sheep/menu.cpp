#include "menu.h"
#include "ui_menu.h"
#include "game.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    qDebug() << "main menu constructed";
    ui->setupUi(this);

    this->setWindowTitle("欢迎来到羊了个羊的世界");
    QPixmap Images("../../../../sheep_and_sheep/pictures/background_picture/main_menu.jpg");
    QPalette Palette = this->palette();
    Images = Images.scaled(this->size());
    Palette.setBrush(QPalette::Window, Images);
    setPalette(Palette);

}

Menu::~Menu()
{
    qDebug() << "main menu destructed";
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    qDebug() << "quit game";
    rejected();
    //也可以通过 按F4进入信号和槽编辑状态，拖动 pushButton到对话框窗体，
    //然后添加 clicked() - accept槽
    //MyWidget w;
    //w.show();
}

void Menu::on_pushButton_easy_clicked()
{
    qDebug() << "start easy game";
    Game dlg(1);
    qDebug() << "child menu loaded";
    dlg.exec();
}
void Menu::on_pushButton_medium_clicked()
{
    qDebug() << "start medium game";
    Game dlg(2);
    dlg.exec();
}
void Menu::on_pushButton_hard_clicked()
{
    qDebug() << "start hard game";
    Game dlg(3);
    dlg.exec();
}
void Menu::on_pushButton_hell_clicked()
{
    qDebug() << "start hell game";
    Game dlg(4);
    dlg.exec();
}
