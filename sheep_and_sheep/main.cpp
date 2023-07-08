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
    dialog.exec();
    return 0;
}
