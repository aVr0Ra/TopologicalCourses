#include "addcoursegui.h"
#include "ui_addcoursegui.h"

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

AddCourseGUI::AddCourseGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCourseGUI)
{
    ui->setupUi(this);

    this->resize(800 , 600);
    this->setWindowTitle("从GUI中添加课程关系");


    QScrollArea *scrollarea = new QScrollArea(this);
    QWidget *mainWidget = new QWidget;
    mainLayout = new QFormLayout;
    mainWidget->setLayout(mainLayout);


    scrollarea->setWidget(mainWidget); // 将mainWidget设置为scrollarea的子widget
    scrollarea->setWidgetResizable(true); // 允许scrollarea根据内容调整大小

    /*第一行：每学期最大学分，横向布局管理器*/
    QLabel *maxCreditlabel = new QLabel("每学期最大学分：");
    maxCreditlabel->setFixedSize(100 , 30);

    QLineEdit *maxCredit = new QLineEdit;
    maxCredit->setFixedSize(100 , 30);

    QPushButton *confirm = new QPushButton("确认所有先修关系信息");
    confirm->setFixedSize(250 , 30);

    QPushButton *quitToMainWidget = new QPushButton("关闭此页面（先修内容将丢失！）");
    quitToMainWidget->setFixedSize(300 , 30);

    QHBoxLayout *maxCreditLayout = new QHBoxLayout;
    maxCreditLayout->addWidget(maxCreditlabel);
    maxCreditLayout->addWidget(maxCredit);
    maxCreditLayout->addWidget(confirm);
    maxCreditLayout->addWidget(quitToMainWidget);
    maxCreditLayout->addStretch(1);

    mainLayout->addRow(maxCreditLayout);


    //中间可滚动区域，递归生成先修条目
    addEntry();


    //设置布局
    QVBoxLayout *windowLayout = new QVBoxLayout;
    windowLayout->addWidget(scrollarea);
    this->setLayout(windowLayout);


    //设置槽函数连接
    connect(confirm, &QPushButton::clicked, [=](){
        //emit this->back();
    });

    connect(quitToMainWidget ,  &QPushButton::clicked, [=](){
        emit this->back();
    });
}

AddCourseGUI::~AddCourseGUI()
{
    delete ui;
}
