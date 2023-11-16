#ifndef ADDCOURSEGUI_H
#define ADDCOURSEGUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLabel>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QList>
#include <QByteArray>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <map>

namespace Ui {
class AddCourseGUI;
}

class AddCourseGUI : public QWidget
{
    Q_OBJECT

signals:
    void back();

private slots:
    void addEntry() {
        QWidget *entryWidget = new QWidget;
        QHBoxLayout *entryLayout = new QHBoxLayout(entryWidget);

        QLabel *label1 = new QLabel("先修信息：", entryWidget);
        QLineEdit *lineEdit1 = new QLineEdit(entryWidget);
        QLabel *label2 = new QLabel("是", entryWidget);
        QLineEdit *lineEdit2 = new QLineEdit(entryWidget);
        QLabel *label3 = new QLabel("的先修课程。" , entryWidget);
        QPushButton *confirmButton = new QPushButton("确认", entryWidget);


        entryLayout->addWidget(label1);
        entryLayout->addWidget(lineEdit1);
        entryLayout->addWidget(label2);
        entryLayout->addWidget(lineEdit2);
        entryLayout->addWidget(label3);
        entryLayout->addWidget(confirmButton);

        mainLayout->addRow(entryWidget);

        connect(confirmButton, &QPushButton::clicked, [=](){
            addEntry();
        });
    }

public:
    explicit AddCourseGUI(QWidget *parent = nullptr);
    ~AddCourseGUI();

    QFormLayout *mainLayout;

private:
    Ui::AddCourseGUI *ui;
};



#endif // ADDCOURSEGUI_H
