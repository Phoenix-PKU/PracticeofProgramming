#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include "card.h"
#include "gamestate.h"
#include "slot.h"
#include <iostream>
#include "main_menu.h"



class ClickableBox : public QWidget
{
public:
    ClickableBox(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        qDebug() << "Box clicked!";
        std::cout << "d" << std::endl;
        QWidget::mousePressEvent(event);
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;
    //ClickableBox box;
    //w.show();
    //box.show();
    //box.close();
    Main_Menu dialog;                        // 新建MyDialog类对象
    qDebug() << "mydialog exec started";
    dialog.exec();
    /*if(dialog.exec()==MyDialog::Accepted){
        w.show();
    }*/
    qDebug() << "mydialog exec finished";
    return app.exec();

    if (true){
        Gamestate game;
        game.play();
    }


    return app.exec();
}
