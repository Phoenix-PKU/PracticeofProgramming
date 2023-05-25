#ifndef LOADPIC_H
#define LOADPIC_H

template <class Gui, class Win>
void setup_background(Gui * ui, Win *window, const char * title
    , const char * pic_dir, int size_x = 0, int size_y = 0){
    ui->setupUi(window);
    window->setWindowTitle(title);
    if (size_x != 0 && size_y != 0)
        window->setFixedSize(size_x, size_y); 
    QPixmap Images(pic_dir);
    QPalette Palette = window->palette();
    Images = Images.scaled(window->size());
    Palette.setBrush(QPalette::Window, Images);
    window->setPalette(Palette);
}

#endif