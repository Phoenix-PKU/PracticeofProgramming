#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include "card.h"
#include "slot.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Menu dialog;                     
    qDebug() << "mydialog exec started";
    dialog.exec();
    qDebug() << "mydialog exec finished";
    return 0;
}
