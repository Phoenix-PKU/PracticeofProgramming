#ifndef GameOverBox_H
#define GameOverBox_H

#include <QDialog>

namespace Ui {
class GameOverBox;
}

class GameOverBox : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverBox(const char * status, QWidget *parent = 0);
    ~GameOverBox();
private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::GameOverBox *ui;
};

#endif // GameOverBox_H
