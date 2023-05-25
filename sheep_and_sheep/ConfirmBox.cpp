#include "ConfirmBox.h"
#include "ui_ConfirmBox.h"
#include "menu.h"

ConfirmBox::ConfirmBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmBox)
{
    qDebug() << "ConfirmBox constructed";
    ui->setupUi(this);

    this->setWindowTitle("您确认要退出吗？");
    this->setFixedSize(240, 100); //设置窗体固定大小
    QPixmap Images("../../../../sheep_and_sheep/pictures/background_picture/warning.jpg");
    QPalette Palette = this->palette();
    Images = Images.scaled(this->size());
    Palette.setBrush(QPalette::Window, Images);
    setPalette(Palette);
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

