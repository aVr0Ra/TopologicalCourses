#include "schedule.h"
#include "ui_schedule.h"

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
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QTableWidget>

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

const int mapx[42] = {1 , 2 , 1 , 2 , 1 , 2 , 1 , 2 , 1 , 2 ,
                      3 , 4 , 3 , 4 , 3 , 4 , 3 , 4 , 3 , 4 ,
                      5 , 6 , 5 , 6 , 5 , 6 , 5 , 6 , 5 , 6 ,
                      1 , 2 , 3 , 4 , 5 , 6 ,
                      1 , 2 , 3 , 4 , 5 , 6};
const int mapy[42] = {1 , 2 , 3 , 4 , 5 , 1 , 2 , 3 , 4 , 5 ,
                      1 , 2 , 3 , 4 , 5 , 1 , 2 , 3 , 4 , 5 ,
                      1 , 2 , 3 , 4 , 5 , 1 , 2 , 3 , 4 , 5 ,
                      6 , 6 , 6 , 6 , 6 , 6 ,
                      7 , 7 , 7 , 7 , 7 , 7};

class DepthNode {
public:
    QByteArray name;
    int depth;
};

bool cmp(DepthNode a , DepthNode b) {
    return a.depth < b.depth;
}

schedule::schedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedule)
{
    ui->setupUi(this);

    qDebug() << "schedule.cpp started";

    this->setFixedSize(1920 , 1080);
    this->setWindowTitle("查看预设课程表");

    //setting layout
    QGridLayout *layout = new QGridLayout(this);
    QPushButton *ret = new QPushButton("返回", this);


    // processing depth
    QFile depthFile("depth.txt");
    if (!depthFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return ;
    }

    DepthNode dn[100];
    int linecount = 1;

    while (!depthFile.atEnd()) {
        QByteArray line = depthFile.readLine();

        int linelength = line.length();

        if (line[0] == 'e') {
            break;
        }

        QByteArray name = "";

        int now = 0;
        for ( ; now < linelength ; ) {
            if (line[now] == ' ') {
                break;
            }
            name.append(line[now]);
            now ++;
        }

        now ++;

        int currentdepth = 0;

        for ( ; now < linelength ; ) {
            if (line[now] == ' ' || line[now] == '\n') {
                break;
            }

            currentdepth = currentdepth * 10 + line[now] - '0';
            now ++;
        }


        qDebug() << "name = " << name << "; and depth = " << currentdepth << " ; linecount = " << linecount;

        dn[linecount].name = name;
        dn[linecount].depth = currentdepth;

        linecount ++;
    }

    linecount --;

    qDebug() << "linecount = " << linecount;

    depthFile.close();

    //depth debug

    for (int i = 1 ; i <= linecount ; i ++) {
        qDebug() << dn[i].name << " " << dn[i].depth;
    }

    sort(dn + 1 , dn + linecount + 1 , cmp);

    int nodecount = linecount;

    int gridrow = 0 , gridcolumn = 0;

    string numbers[9] = {"" , "一" , "二" , "三" , "四" , "五" , "六" , "七" , "八"};

    for (int i = 1 ; i <= 8 ; i ++) {
        QVBoxLayout *curTableLayout = new QVBoxLayout;

        //添加每一个表的标题
        QString qslabel = "";
        qslabel.append("第");
        qslabel.append(numbers[i]);
        qslabel.append("学期课表");

        QLabel *curlabel = new QLabel(qslabel);
        curTableLayout->addWidget(curlabel);


        QTableWidget *tableWidget = new QTableWidget(this);
        tableWidget->setRowCount(7); // 设置行数
        tableWidget->setColumnCount(7); // 设置列数

        // 设置行列 headers
        QStringList hheaders;
        hheaders << "一" << "二" << "三" << "四" << "五" << "六" << "日";
        tableWidget->setHorizontalHeaderLabels(hheaders);

        QStringList vheaders;
        vheaders << "" << "1+2" << "3+4" << "5+6" << "7+8" << "9+10" << "11+12";
        tableWidget->setVerticalHeaderLabels(vheaders);

        for (int j = 0 ; j < 7 ; j ++) {
            tableWidget->setRowHeight(j , 43);
        }

        for (int j = 0 ; j < 8 ; j ++) {
            tableWidget->setColumnWidth(j , 83);
        }

        // 添加项目到表格
        // tableWidget->setItem(0, 1, new QTableWidgetItem("Item 2"));

        int curDepthCourseCount = 0;


        for (int node = 1 ; node <= nodecount ; node ++) {
            if (dn[node].depth == i) {
                tableWidget->setItem(mapx[curDepthCourseCount] - 1 , mapy[curDepthCourseCount] - 1 ,
                                     new QTableWidgetItem(dn[node].name));

                curDepthCourseCount ++;
            }
        }

        curTableLayout->addWidget(tableWidget);
        layout->addLayout(curTableLayout , gridrow , gridcolumn);
        gridcolumn ++;

        if (gridcolumn == 3) {
            gridcolumn = 0;
            gridrow ++;
        }
    }

    layout->addWidget(ret);


    this->setLayout(layout);


    //返回按钮
    connect(ret, &QPushButton::clicked, [=](){
        emit this->back();
    });
}

schedule::~schedule()
{
    delete ui;
}
