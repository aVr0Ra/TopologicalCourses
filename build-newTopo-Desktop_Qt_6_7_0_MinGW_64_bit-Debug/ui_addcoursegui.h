/********************************************************************************
** Form generated from reading UI file 'addcoursegui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOURSEGUI_H
#define UI_ADDCOURSEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddCourseGUI
{
public:

    void setupUi(QWidget *AddCourseGUI)
    {
        if (AddCourseGUI->objectName().isEmpty())
            AddCourseGUI->setObjectName("AddCourseGUI");
        AddCourseGUI->resize(1606, 870);

        retranslateUi(AddCourseGUI);

        QMetaObject::connectSlotsByName(AddCourseGUI);
    } // setupUi

    void retranslateUi(QWidget *AddCourseGUI)
    {
        AddCourseGUI->setWindowTitle(QCoreApplication::translate("AddCourseGUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddCourseGUI: public Ui_AddCourseGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOURSEGUI_H
