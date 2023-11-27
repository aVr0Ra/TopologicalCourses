/********************************************************************************
** Form generated from reading UI file 'schedule.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULE_H
#define UI_SCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_schedule
{
public:

    void setupUi(QWidget *schedule)
    {
        if (schedule->objectName().isEmpty())
            schedule->setObjectName("schedule");
        schedule->resize(400, 300);

        retranslateUi(schedule);

        QMetaObject::connectSlotsByName(schedule);
    } // setupUi

    void retranslateUi(QWidget *schedule)
    {
        schedule->setWindowTitle(QCoreApplication::translate("schedule", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class schedule: public Ui_schedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULE_H
