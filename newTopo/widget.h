#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "newwidget.h"
#include "addcoursegui.h"

#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public slots:

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    newwidget *ppage = NULL;
    AddCourseGUI *addcoursegui_page = NULL;
};
#endif // WIDGET_H
