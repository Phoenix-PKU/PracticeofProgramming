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
/*
class MovableFrame : public QFrame
{
public:
    MovableFrame(QWidget *parent = nullptr)
        : QFrame(parent)
    {
        setStyleSheet("background-color: white; border: 1px solid black;");
    }

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            m_dragPos = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton)
        {
            move(event->globalPos() - m_dragPos);
            event->accept();
        }
    }

private:
    QPoint m_dragPos;
};*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // MovableFrame *frame = new MovableFrame(this);
   // frame->setGeometry(50, 50, 200, 200);
   // frame->show();

    ClickableBox box;
    box.show();

    return app.exec();
}
