#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QPushButton>

#define BAR_XPOS 140
#define BAR_YPOS 20
#define BAR_LEN 545
#define BAR_HEIGHT 40
#define MAXLINE 128

class Bar:public QPushButton
{
    Q_OBJECT
    double len;
public:
    const char * name;
    void set_len(double _len);
    Bar(const char * _name, double _len,
        QDialog * parent);
    ~Bar(void);
};

#endif // PROGRESSBAR_H
