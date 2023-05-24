#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

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
    void on_pushButton_easy_clicked();

    void on_pushButton_medium_clicked();

    void on_pushButton_hard_clicked();

    void on_pushButton_hell_clicked();

    void on_pushButton_clicked();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
