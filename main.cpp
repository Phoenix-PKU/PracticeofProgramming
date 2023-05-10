#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class ClickableBox : public QWidget
{
public:
    ClickableBox(QWidget *parent = nullptr) : QWidget(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        qDebug() << "Box clicked!";
        printf("changed by LiLei at 5/10 21:54\n");
        printf("hello by aiyiwen\n");
        printf("hello by lilei at 5/10 23:24\n");
	QWidget::mousePressEvent(event);
    }


};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ClickableBox box;
    box.show();

    return app.exec();
}
