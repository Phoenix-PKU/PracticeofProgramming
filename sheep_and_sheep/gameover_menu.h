#ifndef Gameover_Menu_H
#define Gameover_Menu_H

#include <QDialog>

namespace Ui {
class Gameover_Menu;
}

class Gameover_Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Gameover_Menu(const char * status, QWidget *parent = 0);
    ~Gameover_Menu();
private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::Gameover_Menu *ui;
};

#endif // Gameover_Menu_H
