#ifndef Confirm_Box_H
#define Confirm_Box_H

#include <QDialog>

namespace Ui {
class Confirm_Box;
}

class Confirm_Box : public QDialog
{
    Q_OBJECT

public:
    explicit Confirm_Box(QWidget *parent = 0);
    ~Confirm_Box();
private slots:
    void on_pushButton_goback_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::Confirm_Box *ui;
};

#endif // Confirm_Box_H
