#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

struct GameParameters;
namespace Ui {
class MyDialog;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_easy_clicked();

    void on_medium_clicked();

    void on_hard_clicked();

    void on_hell_clicked();

    void on_quit_clicked();
    
    void startGame(const GameParameters& params);

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
