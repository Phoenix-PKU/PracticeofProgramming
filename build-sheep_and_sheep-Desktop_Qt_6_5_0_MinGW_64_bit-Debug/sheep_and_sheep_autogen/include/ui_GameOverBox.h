/********************************************************************************
** Form generated from reading UI file 'GameOverBox.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEOVERBOX_H
#define UI_GAMEOVERBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GameOverBox
{
public:
    QPushButton *goToMainMenu;

    void setupUi(QDialog *GameOverBox)
    {
        if (GameOverBox->objectName().isEmpty())
            GameOverBox->setObjectName("GameOverBox");
        GameOverBox->resize(355, 199);
        goToMainMenu = new QPushButton(GameOverBox);
        goToMainMenu->setObjectName("goToMainMenu");
        goToMainMenu->setGeometry(QRect(110, 120, 141, 41));

        retranslateUi(GameOverBox);
        QObject::connect(goToMainMenu, &QPushButton::clicked, GameOverBox, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(GameOverBox);
    } // setupUi

    void retranslateUi(QDialog *GameOverBox)
    {
        GameOverBox->setWindowTitle(QCoreApplication::translate("GameOverBox", "Dialog", nullptr));
        goToMainMenu->setText(QCoreApplication::translate("GameOverBox", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameOverBox: public Ui_GameOverBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEOVERBOX_H
