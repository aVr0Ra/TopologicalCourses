#include "creditsandlimitations.h"
#include "ui_creditsandlimitations.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QList>
#include <QByteArray>
#include <QTableWidget>
#include <QMessageBox>

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
#include <cstdlib>
#include <string>

using namespace std;

class Node {
public:
    QByteArray name;
    int ind , outd;
    int countedges;
    int id;
    int credits;

    int destinations[100];
    int depth = 0;
};

void dfs(Node node[] , int now , int depth , int depthLimits[]) {
    if (node[now].depth >= depth) {
        return ;
    }

    if (depthLimits[depth] < node[now].credits) {
        dfs(node , now , depth + 1 , depthLimits);
        return ;
    }

    node[now].depth = depth;
    depthLimits[depth] -= node[now].credits;

    for (int i = 1 ; i <= node[now].countedges ; i ++) {
        dfs(node , node[now].destinations[i] , depth + 1 , depthLimits);
    }

    return ;
}


CreditsAndLimitations::CreditsAndLimitations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditsAndLimitations)
{
    ui->setupUi(this);

    qDebug() << "!!! Credits and Limitations .cpp begins !!!";

    this->resize(800 , 600);
    this->setWindowTitle("设置课程学分和限制关系");

    QScrollArea *scrollarea = new QScrollArea(this);
    QWidget *mainWidget = new QWidget;
    QFormLayout *layout = new QFormLayout;
    mainWidget->setLayout(layout);


    scrollarea->setWidget(mainWidget); // 将mainWidget设置为scrollarea的子widget
    scrollarea->setWidgetResizable(true); // 允许scrollarea根据内容调整大小


    QPushButton *ret = new QPushButton("确认以上所有课程的学分和限制关系");


    /*第一行：每学期最大学分，横向布局管理器*/
    QHBoxLayout *creditsLimitations = new QHBoxLayout;
    QLabel *maxCreditlabel = new QLabel("每学期最大学分：（无输入代表无学分限制）");
    maxCreditlabel->setFixedSize(250 , 30);
    QLineEdit *maxCredit = new QLineEdit;
    maxCredit->setFixedSize(500 , 30);

    creditsLimitations->addWidget(maxCreditlabel);
    creditsLimitations->addWidget(maxCredit);

    layout->addRow(creditsLimitations);

    /*接下来：循环输入每一门课的学分*/
    // 8个学期最多336门课

    //进行预处理，寻找一共有多少门课程
    QFile inputfile("in.txt");
    if (!inputfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return ;
    }

    QByteArray pathfrom[100] , pathto[100];

    int linecount = 1 , nodecount = 0;
    int edges[100][2];

    map <QByteArray , int> M;

    Node node[200];

    while (!inputfile.atEnd()) {
        QByteArray line = inputfile.readLine();

        int linelength = line.length();

        int now = 0;

        pathfrom[linecount] = "";
        pathto[linecount] = "";

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

        linecount ++;
    }

    inputfile.close();

    // qDebug() << "nodecount = " << nodecount;

    // 添加课程学分
    QLabel *allCoursesLabels[350];
    QLabel *allCoursesLastLabels[350];
    QLabel *allCoursesMidLabels[350];

    QLineEdit *allCoursesCredits[350];
    QLineEdit *allCoursesLimits[350];

    QHBoxLayout *allCoursesLayouts[350];

    for (int i = 1 ; i <= nodecount ; i ++) {
        QString cur = "";
        cur.append(node[i].name);
        cur.append(" 课程的学分为：");

        allCoursesLabels[i] = new QLabel(cur);

        allCoursesCredits[i] = new QLineEdit;
        allCoursesLimits[i] = new QLineEdit;

        allCoursesCredits[i]->setFixedWidth(50);
        allCoursesLimits[i]->setFixedWidth(50);

        allCoursesMidLabels[i] = new QLabel(" 学分，您希望该门课在第 ");
        allCoursesLastLabels[i] = new QLabel(" 学期进行（学分不可空白，制定学期空白代表不指定）");


        allCoursesLayouts[i] = new QHBoxLayout;

        allCoursesLayouts[i]->addWidget(allCoursesLabels[i]);
        allCoursesLayouts[i]->addWidget(allCoursesCredits[i]);
        allCoursesLayouts[i]->addWidget(allCoursesMidLabels[i]);
        allCoursesLayouts[i]->addWidget(allCoursesLimits[i]);
        allCoursesLayouts[i]->addWidget(allCoursesLastLabels[i]);

        allCoursesLayouts[i]->addStretch(1);

        layout->addRow(allCoursesLayouts[i]);
    }




    // 添加返回按钮
    layout->addRow(ret);

    // 设置layout
    QVBoxLayout *windowLayout = new QVBoxLayout;
    windowLayout->addWidget(scrollarea);
    this->setLayout(windowLayout);


    QByteArray backupName[100];

    qDebug() << "\n进入connect之前的名字如下：";

    for (int i = 1 ; i <= nodecount ; i ++) {
        backupName[i] = node[i].name;
        qDebug() << node[i].name;
    }

    // 开始处理数据，并产生depth.txt
    connect(ret , &QPushButton::clicked , [this , &node , nodecount , allCoursesCredits , allCoursesLimits , maxCredit , linecount , edges , backupName](){

        qDebug() << "已经进入，connect，debug名字";

        // 处理所有的限制条件和学分条件，存放到 node[] 中
        for (int i = 1 ; i <= nodecount ; i ++) {
            qDebug() << backupName[i] << " " << node[i].depth;
        }

        for (int i = 1 ; i <= nodecount ; i ++) {
            QString cred = allCoursesCredits[i]->text() , lim = allCoursesLimits[i]->text();

            if (cred.isEmpty()) {
                QString warningString;
                warningString.append(node[i].name);
                warningString.append("课程的学分为空！请重新输入");

                QMessageBox::warning(this , "输入为空" , warningString);
                return ;
            }

            node[i].credits = cred.toInt();

            if (!lim.isEmpty()) {
                node[i].depth = lim.toInt();
            }
            else {
                node[i].depth = 0;
            }
        }

        // 进行 dfs

        int depthLimits[10];

        if (maxCredit->text().isEmpty()) {
            for (int i = 1 ; i <= 8 ; i ++) {
                depthLimits[i] = 1e9 + 7;
            }
        }
        else {
            for (int i = 1 ; i <= 8 ; i ++) {
                depthLimits[i] = maxCredit->text().toInt();
            }
        }




        for (int i = 1 ; i <= nodecount ; i ++) {
            if (!node[i].ind) {
                dfs(node , i , 1 , depthLimits);
            }
        }

        qDebug() << "dfs finished";

        for (int i = 1 ; i <= nodecount ; i ++) {
            qDebug() << node[i].name << " " << node[i].depth;

            if (node[i].depth >= 9) {
                QMessageBox::warning(this, "警告", "在8学期内无法完成预定课程，请重新输入");
                emit this->back();
                return ;
            }
        }

        //output depth into depth.txt for newwidget.cpp to paint

        QFile outputFile("depth.txt");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) return;

        outputFile.write("\xEF\xBB\xBF"); // 写入 UTF-8 BOM
        QTextStream out(&outputFile);
        out.setEncoding(QStringConverter::Utf8);

        for (int i = 1 ; i <= nodecount ; i ++) {
            QByteArray d = "";
            int dep = node[i].depth;
            while (dep) {
                d.push_front((dep % 10) + '0');
                dep /= 10;
            }

            //qDebug() << d;

            QByteArray currentWritingLine = "";

            currentWritingLine.append(node[i].name);
            currentWritingLine.append(" ");
            currentWritingLine.append(d);
            currentWritingLine.append("\n");

            //currentWritingLine.append(" " + d + "\n");

            qDebug() << currentWritingLine;

            outputFile.write(currentWritingLine);
        }

        outputFile.write("e\n");

        //qDebug() << "depth writed successfully";

        int edgecount = linecount - 1;

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
            //qDebug() << currentWritingLine;
            outputFile.write(currentWritingLine);
        }

        outputFile.close();


        // 返回信号
        QMessageBox::information(this , "确认" , "信息已确认");
        emit this->back();
    });
}

CreditsAndLimitations::~CreditsAndLimitations()
{
    delete ui;
}
