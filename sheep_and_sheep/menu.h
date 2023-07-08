#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QtMultimedia/QSoundEffect>

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
    QSoundEffect *bgm_menu, *click_menu;

private slots:
    void on_easy_clicked();

    void on_medium_clicked();

    void on_hard_clicked();

    void on_hell_clicked();

    void on_quit_clicked();
    
    void startGame(const GameParameters& params);

    void setBgmVolume(int value);

    void setClickVolume(int value);

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
