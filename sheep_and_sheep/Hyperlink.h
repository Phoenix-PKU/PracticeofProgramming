#ifndef Hyperlink_H
#define Hyperlink_H

#include <QDialog>
#include <QLabel>
#include <QEvent>

namespace Ui {
class Hyperlink;
}

class Hyperlink : public QDialog
{
    Q_OBJECT
    int * p_left_time;

public:
    explicit Hyperlink(int * _p_left_time,QWidget *parent = 0);
    ~Hyperlink();
private slots:
    bool eventFilter(QObject *watched, QEvent *event);
    void on_no_clicked();

private:
    Ui::Hyperlink *ui;
};

#endif // Hyperlink_H
