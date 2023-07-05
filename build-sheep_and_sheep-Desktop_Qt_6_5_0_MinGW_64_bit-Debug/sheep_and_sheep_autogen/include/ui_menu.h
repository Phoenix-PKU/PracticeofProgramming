/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QPushButton *quit;
    QPushButton *easy;
    QPushButton *medium;
    QPushButton *hard;
    QPushButton *hell;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName("MyDialog");
        MyDialog->resize(400, 300);
        quit = new QPushButton(MyDialog);
        quit->setObjectName("quit");
        quit->setGeometry(QRect(160, 260, 75, 23));
        easy = new QPushButton(MyDialog);
        easy->setObjectName("easy");
        easy->setGeometry(QRect(30, 50, 131, 71));
        medium = new QPushButton(MyDialog);
        medium->setObjectName("medium");
        medium->setGeometry(QRect(220, 50, 131, 71));
        hard = new QPushButton(MyDialog);
        hard->setObjectName("hard");
        hard->setGeometry(QRect(30, 150, 131, 71));
        hell = new QPushButton(MyDialog);
        hell->setObjectName("hell");
        hell->setGeometry(QRect(220, 150, 131, 71));

        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QCoreApplication::translate("MyDialog", "Dialog", nullptr));
        quit->setText(QCoreApplication::translate("MyDialog", "QUIT", nullptr));
        easy->setText(QCoreApplication::translate("MyDialog", "easy", nullptr));
        medium->setText(QCoreApplication::translate("MyDialog", "medium", nullptr));
        hard->setText(QCoreApplication::translate("MyDialog", "hard", nullptr));
        hell->setText(QCoreApplication::translate("MyDialog", "hell", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
