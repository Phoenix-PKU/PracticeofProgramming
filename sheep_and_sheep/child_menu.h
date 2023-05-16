#ifndef Child_Menu_H
#define Child_Menu_H

#include <QDialog>
#include "main_menu.h"

namespace Ui {
class Child_Menu;
}

class Child_Menu : public QDialog
{
    Q_OBJECT
    int index;
    Main_Menu *p;

public:
    explicit Child_Menu(int i,QWidget *parent = 0);
    ~Child_Menu();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Child_Menu *ui;
};

#endif // Child_Menu_H
