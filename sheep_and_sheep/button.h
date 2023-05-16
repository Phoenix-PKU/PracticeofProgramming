
#include <qpushbutton.h>
#include <iostream>
class MyButton:public QPushButton{
public:
    MyButton(QWidget *parent);
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        qDebug() << "Box clicked!";
        std::cout << "d" << std::endl;
        QWidget::mousePressEvent(event);
    }
};
