/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QPushButton *confirmBox;
    QPushButton *myshuffle;

    void setupUi(QDialog *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName("Game");
        Game->resize(516, 457);
        confirmBox = new QPushButton(Game);
        confirmBox->setObjectName("confirmBox");
        confirmBox->setGeometry(QRect(0, 0, 61, 31));
        myshuffle = new QPushButton(Game);
        myshuffle->setObjectName("myshuffle");
        myshuffle->setGeometry(QRect(10, 380, 61, 61));

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QDialog *Game)
    {
        Game->setWindowTitle(QCoreApplication::translate("Game", "Dialog", nullptr));
        confirmBox->setText(QCoreApplication::translate("Game", "return", nullptr));
        myshuffle->setText(QCoreApplication::translate("Game", "Shuffle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
