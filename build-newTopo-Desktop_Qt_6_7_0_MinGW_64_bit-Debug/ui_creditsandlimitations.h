/********************************************************************************
** Form generated from reading UI file 'creditsandlimitations.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITSANDLIMITATIONS_H
#define UI_CREDITSANDLIMITATIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreditsAndLimitations
{
public:

    void setupUi(QWidget *CreditsAndLimitations)
    {
        if (CreditsAndLimitations->objectName().isEmpty())
            CreditsAndLimitations->setObjectName("CreditsAndLimitations");
        CreditsAndLimitations->resize(400, 300);

        retranslateUi(CreditsAndLimitations);

        QMetaObject::connectSlotsByName(CreditsAndLimitations);
    } // setupUi

    void retranslateUi(QWidget *CreditsAndLimitations)
    {
        CreditsAndLimitations->setWindowTitle(QCoreApplication::translate("CreditsAndLimitations", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreditsAndLimitations: public Ui_CreditsAndLimitations {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITSANDLIMITATIONS_H
