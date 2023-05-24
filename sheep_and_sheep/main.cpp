#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include "card.h"
#include "slot.h"
#include <iostream>
#include "main_menu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QWidget w;
    Main_Menu dialog;                        // 新建MyDialog类对象

    qDebug() << "mydialog exec started";

    /*if(dialog.exec() == QDialog::Accepted){
        //w.show();
        return app.exec();
    }*/

    dialog.exec();
    qDebug() << "mydialog exec finished";
    return 0;
    //return app.exec();
}
