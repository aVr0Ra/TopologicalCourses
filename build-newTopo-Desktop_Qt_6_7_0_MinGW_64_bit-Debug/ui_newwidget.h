/********************************************************************************
** Form generated from reading UI file 'newwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWWIDGET_H
#define UI_NEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newwidget
{
public:

    void setupUi(QWidget *newwidget)
    {
        if (newwidget->objectName().isEmpty())
            newwidget->setObjectName("newwidget");
        newwidget->resize(1378, 890);

        retranslateUi(newwidget);

        QMetaObject::connectSlotsByName(newwidget);
    } // setupUi

    void retranslateUi(QWidget *newwidget)
    {
        newwidget->setWindowTitle(QCoreApplication::translate("newwidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newwidget: public Ui_newwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWWIDGET_H
