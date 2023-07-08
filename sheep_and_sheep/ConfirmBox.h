#ifndef ConfirmBox_H
#define ConfirmBox_H

#include <QDialog>
#include "game.h"

#define BGM_SLIDER_RATIO 5000.0
#define CLICK_SLIDER_RATIO 100.0
#define MENUBGM_SLIDER_RATIO 5000.0

namespace Ui {
class ConfirmBox;
}

class Game;

class ConfirmBox : public QDialog
{
    Q_OBJECT

public:
    const char * type;
    QDialog * lastpage;
    explicit ConfirmBox(const char * _type,
                        QDialog * _lastpage, QWidget *parent = 0);
    ~ConfirmBox();

private slots:
    void on_goback_clicked();

    void on_confirm_clicked();

    void on_bgmSlider_valueChanged(int value);

    void on_clickSlider_valueChanged(int value);

private:
    Ui::ConfirmBox *ui;
};

#endif // ConfirmBox_H
