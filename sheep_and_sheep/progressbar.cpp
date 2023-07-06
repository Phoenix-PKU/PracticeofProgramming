#include "progressbar.h"
#include "game.h"

Bar::Bar(const char * _name, double _len,
         QDialog * parent):
    name(_name),
    len(_len),
    QPushButton(parent)
{
    this->setEnabled(false);

    this->setGeometry(BAR_XPOS, BAR_YPOS, len, BAR_HEIGHT);
    this->setObjectName("bar_" + (std::string)name);

    char arg[MAXLINE];
    strcpy(arg, "QPushButton{border-image: url("
                ":/new/prefix1/pictures/background_picture/");
    strcpy(arg + strlen(arg), name);
    strcpy(arg + strlen(arg), ".png);}");
    this->setStyleSheet(arg);
}

Bar::~Bar(void){

}

void Bar::set_len(double _len)
{
    len = _len;
    this->setGeometry(BAR_XPOS, BAR_YPOS, len, BAR_HEIGHT);
}
