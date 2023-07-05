/********************************************************************************
** Form generated from reading UI file 'ConfirmBox.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIRMBOX_H
#define UI_CONFIRMBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfirmBox
{
public:
    QPushButton *confirm;
    QPushButton *goback;

    void setupUi(QDialog *ConfirmBox)
    {
        if (ConfirmBox->objectName().isEmpty())
            ConfirmBox->setObjectName("ConfirmBox");
        ConfirmBox->resize(234, 96);
        confirm = new QPushButton(ConfirmBox);
        confirm->setObjectName("confirm");
        confirm->setGeometry(QRect(20, 20, 71, 51));
        goback = new QPushButton(ConfirmBox);
        goback->setObjectName("goback");
        goback->setGeometry(QRect(130, 20, 71, 51));

        retranslateUi(ConfirmBox);
        QObject::connect(confirm, &QPushButton::clicked, ConfirmBox, qOverload<>(&QDialog::accept));
        QObject::connect(goback, &QPushButton::clicked, ConfirmBox, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ConfirmBox);
    } // setupUi

    void retranslateUi(QDialog *ConfirmBox)
    {
        ConfirmBox->setWindowTitle(QCoreApplication::translate("ConfirmBox", "Dialog", nullptr));
        confirm->setText(QCoreApplication::translate("ConfirmBox", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        goback->setText(QCoreApplication::translate("ConfirmBox", "\350\277\224\345\233\236\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfirmBox: public Ui_ConfirmBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIRMBOX_H
