#ifndef ConfirmBox_H
#define ConfirmBox_H

#include <QDialog>

namespace Ui {
class ConfirmBox;
}

class ConfirmBox : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmBox(QWidget *parent = 0);
    ~ConfirmBox();
private slots:
    void on_goback_clicked();

    void on_confirm_clicked();

private:
    Ui::ConfirmBox *ui;
};

#endif // ConfirmBox_H
