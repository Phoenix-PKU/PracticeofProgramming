#include "confirm_box.h"
#include "ui_confirm_box.h"
#include "main_menu.h"

Confirm_Box::Confirm_Box(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirm_Box)
{
    qDebug() << "Confirm_Box constructed";
    ui->setupUi(this);

    this->setWindowTitle("您确认要退出吗？");
    this->setFixedSize(240, 100); //设置窗体固定大小
    QPixmap Images("../../../../sheep_and_sheep/pictures/background_picture/warning.jpg");
    QPalette Palette = this->palette();
    Images = Images.scaled(this->size());
    Palette.setBrush(QPalette::Window, Images);
    setPalette(Palette);
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

