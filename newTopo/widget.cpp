#include "widget.h"
#include "ui_widget.h"
#include "newwidget.h"
#include "addcoursegui.h"

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

using namespace std;

class Node {
public:
    QByteArray name;
    int ind , outd;
    int countedges;
    int id;

    int destinations[100];
    int depth = 0;
};

void dfs(Node node[] , int n , int m , int now , int depth) {
    //qDebug() << "dfs begins";

    if (node[now].depth >= depth) {
        return ;
    }

    node[now].depth = depth;

    for (int i = 1 ; i <= node[now].countedges ; i ++) {
        dfs(node , n , m , node[now].destinations[i] , depth + 1);
    }

    return ;
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(800 , 600);
    this->setWindowTitle("课程管理系统，by 易思铭21071125");

    QPushButton *pb , *selectfile , *addfromGUI , *showschedule;

    addfromGUI = new QPushButton("从GUI中添加课程先后关系");
    addfromGUI->setFixedSize(200 , 50);
    //addfromGUI->move(100 , 100);

    selectfile = new QPushButton("从文件读入数据");
    selectfile->setFixedSize(100 , 50);
    //selectfile->move(200 , 200);

    pb = new QPushButton("显示选课结果拓扑图");
    pb->setFixedSize(200 , 50);
    //pb->move(300 , 300);

    showschedule = new QPushButton("显示课程安排");
    showschedule->setFixedSize(200 , 50);

    //QPixmap *img = new QPixmap;
    //img->load(":/images/top.png");

    QLabel *titleimage = new QLabel("标题图片");
    titleimage->setPixmap(QPixmap(":/images/top.png"));



    QHBoxLayout *hbox = new QHBoxLayout;
    QHBoxLayout *first_row_img = new QHBoxLayout;

    first_row_img->addWidget(titleimage);

    hbox->addWidget(addfromGUI);
    hbox->addWidget(selectfile);
    hbox->addWidget(pb);
    hbox->addWidget(showschedule);


    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *titlelabel = new QLabel("课程管理系统，by 易思铭21071125");

    mainLayout->addWidget(titlelabel);
    mainLayout->addLayout(first_row_img);
    mainLayout->addLayout(hbox);

    this->setLayout(mainLayout);


    connect(selectfile , &QPushButton::clicked , [=](){
        int n = 0 , m = 0;
        QByteArray pathfrom[100] , pathto[100];

        QString filename = QFileDialog::getOpenFileName();
        qDebug() << filename;

        QFile inputfile(filename);
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
            if (linecount == 1) {
                int now = 0;
                while ('0' <= line[now] && line[now] <= '9') {
                    n = n * 10 + line[now] - '0';
                    now ++;
                }

                now ++;

                while ('0' <= line[now] && line[now] <= '9') {
                    m = m * 10 + line[now] - '0';
                    now ++;
                }

                //qDebug() << "n = " << n << "; m = " << m;
            }
            else {
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

                //qDebug() << "pathfrom: " << pathfrom[linecount];
                //qDebug() << "pathto: "<< pathto[linecount];

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
            }

            linecount ++;

            //qDebug() << "end of this line\n";
        }

        //end of inputfile

        //qDebug() << "\n\n\n end of input processing... Now output Nodes";
/*
        for (int i = 1 ; i <= n ; i ++) {
            qDebug() << i << " " << node[i].name;
            qDebug() << "edgescount = " << node[i].countedges;
            for (int j = 1 ; j <= node[i].countedges ; j ++) {
                qDebug() << node[node[i].destinations[j]].name;
            }
        }qDebug() << "\n";*/


        //begining processing data: find depth

        for (int i = 1 ; i <= n ; i ++) {
            if (!node[i].ind) {
                dfs(node , n , m , i , 1);
            }
        }

        //depth debug
        /*for (int i = 1 ; i <= n ; i ++) {
            qDebug() << node[i].name << "; depth = " << node[i].depth;
        }*/


        //output depth into depth.txt for newwidget.cpp to paint
        QFile outputFile("depth.txt");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        for (int i = 1 ; i <= n ; i ++) {
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

        for (int i = 1 ; i <= m ; i ++) {
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


        qDebug() << "widget.cpp ends";
    });


    connect(pb , &QPushButton::clicked , [=](){
        this->ppage = new newwidget;
        //this->hide();
        this->ppage->show();

        connect(this->ppage , &newwidget::back , [=](){
            this->ppage->hide();
        });
    });

    connect(addfromGUI , &QPushButton::clicked , [=](){
        this->addcoursegui_page = new AddCourseGUI;
        this->addcoursegui_page->show();

        connect(this->addcoursegui_page , &AddCourseGUI::back , [=](){
            this->addcoursegui_page->hide();
        });
    });

    connect(showschedule , &QPushButton::clicked , [=](){
        this->curSchedule = new schedule;
        this->curSchedule->show();

        connect(this->curSchedule , &schedule::back , [=](){
            this->curSchedule->hide();
        });
    });
}

Widget::~Widget()
{
    delete ui;
}
