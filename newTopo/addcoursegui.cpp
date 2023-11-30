#include "addcoursegui.h"
#include "ui_addcoursegui.h"
#include "creditsandlimitations.h"

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
#include <QMessageBox>
#include <QByteArray>

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;
/*
class Node {
public:
    QByteArray name;
    int ind , outd;
    int countedges;
    int id;

    int destinations[100];
    int depth = 0;
};

void dfs(Node node[] , int now , int depth) {
    if (node[now].depth >= depth) {
        return ;
    }

    node[now].depth = depth;

    for (int i = 1 ; i <= node[now].countedges ; i ++) {
        dfs(node , node[now].destinations[i] , depth + 1);
    }

    return ;
}
*/
AddCourseGUI::AddCourseGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddCourseGUI)
{
    ui->setupUi(this);

    this->resize(800 , 600);
    this->setWindowTitle("从GUI中添加课程关系");

    //清空原来的in.txt的文件
    QFile file("in.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "in.txt reset";
    }



    QScrollArea *scrollarea = new QScrollArea(this);
    QWidget *mainWidget = new QWidget;
    mainLayout = new QFormLayout;
    mainWidget->setLayout(mainLayout);


    scrollarea->setWidget(mainWidget); // 将mainWidget设置为scrollarea的子widget
    scrollarea->setWidgetResizable(true); // 允许scrollarea根据内容调整大小



    QPushButton *confirm = new QPushButton("确认所有先修关系信息");
    confirm->setFixedSize(750 , 30);

    QHBoxLayout *maxCreditLayout = new QHBoxLayout;
    maxCreditLayout->addWidget(confirm);
    maxCreditLayout->addStretch(1);

    mainLayout->addRow(maxCreditLayout);


    //中间可滚动区域，递归生成先修条目
    addEntry();


    //设置布局
    QVBoxLayout *windowLayout = new QVBoxLayout;
    windowLayout->addWidget(scrollarea);
    this->setLayout(windowLayout);


    //设置槽函数连接，进行dfs
    connect(confirm, &QPushButton::clicked, [=](){
        /*QByteArray pathfrom[100] , pathto[100];

        QFile inputfile("in.txt");
        if (!inputfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return ;
        }

        //line count and node count
        int linecount = 1 , nodecount = 0;

        //map indicates: name to int(index)
        map <QByteArray , int> M;

        int edges[100][2];

        Node node[200];

        //processing every line
        while (!inputfile.atEnd()) {
            QByteArray line = inputfile.readLine();

            int linelength = line.length();

            int now = 0;
            for ( ; now < linelength ; ) {
                if (line[now] == ' ') {
                    break;
                }
                pathfrom[linecount].append(line[now]);
                now ++;
            }

            now ++;

            for ( ; now < linelength ; ) {
                if (line[now] == '\n' || line[now] == ' ') {
                    break;
                }
                pathto[linecount].append(line[now]);
                now ++;
            }

            qDebug() << "pathfrom: " << pathfrom[linecount];
            qDebug() << "pathto: "<< pathto[linecount];

            if (!M[pathfrom[linecount]]) {
                M[pathfrom[linecount]] = ++ nodecount;
                node[nodecount].name = pathfrom[linecount];
            }

            if (!M[pathto[linecount]]) {
                M[pathto[linecount]] = ++ nodecount;
                node[nodecount].name = pathto[linecount];
            }

            //add edge in edges
            edges[linecount - 1][0] = M[pathfrom[linecount]];
            edges[linecount - 1][1] = M[pathto[linecount]];

            //add edge in node
            node[M[pathfrom[linecount]]].destinations[++ node[M[pathfrom[linecount]]].countedges] = M[pathto[linecount]];

            //refresh ind and outd
            node[M[pathfrom[linecount]]].outd ++;
            node[M[pathto[linecount]]].ind ++;

            linecount ++;
        }

        qDebug() << "linecount = " << linecount;

        int edgecount = linecount - 1;

        //begining processing data: find depth

        for (int i = 1 ; i <= nodecount ; i ++) {
            if (!node[i].ind) {
                dfs(node , i , 1);
            }
        }


        //output depth into depth.txt for newwidget.cpp to paint

        QFile outputFile("depth.txt");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

        for (int i = 1 ; i <= nodecount ; i ++) {
            QByteArray d = "";
            int dep = node[i].depth;
            while (dep) {
                d.push_front((dep % 10) + '0');
                dep /= 10;
            }

            //qDebug() << d;

            QByteArray currentWritingLine = node[i].name + " " + d + "\n";
            qDebug() << currentWritingLine;
            outputFile.write(currentWritingLine);
        }

        outputFile.write("e\n");

        for (int i = 0 ; i < edgecount ; i ++) {
            int _begin = edges[i][0] , _end = edges[i][1];
            QByteArray bab("") , bae("");

            while (_begin) {
                bab.push_front((_begin % 10) + '0');
                _begin /= 10;
            }

            while (_end) {
                bae.push_front((_end % 10) + '0');
                _end /= 10;
            }

            QByteArray currentWritingLine = bab + " " + bae + '\n';
            qDebug() << currentWritingLine;
            outputFile.write(currentWritingLine);
        }

        outputFile.close();
        inputfile.close();
*/

        // 显示限制页面
        this->cal = new CreditsAndLimitations;
        this->cal->show();
        this->hide();

        connect(this->cal , &CreditsAndLimitations::back , [=](){
            this->cal->hide();
        });


        emit this->back();
    });
}

AddCourseGUI::~AddCourseGUI()
{
    delete ui;
}
