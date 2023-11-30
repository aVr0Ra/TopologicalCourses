#include "newwidget.h"
#include "ui_newwidget.h"

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
#include <QString>

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

using namespace std;

class DepthNode {
public:
    QByteArray name;
    int depth;

    int x , y;

    int id;

    bool operator < (const DepthNode &k) const {
        return depth < k.depth;
    }
};

newwidget::newwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newwidget)
{
    ui->setupUi(this);


    qDebug() << "\n!!! Topo Graph Begins !!!";

    this->resize(1600 , 900);
    this->setWindowTitle("查看拓扑图");

    QPushButton *ret = new QPushButton("返回", this);


    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addStretch(1);

    ret->setMinimumSize(600, 50);

    layout->addWidget(ret, 0, Qt::AlignHCenter);

    this->setLayout(layout);

    connect(ret, &QPushButton::clicked, [=](){
        emit this->back();
    });
}

newwidget::~newwidget()
{
    delete ui;
}

void newwidget::paintEvent(QPaintEvent *event) {
    // processing input
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
        dn[linecount].id = linecount;

        linecount ++;
    }

    linecount --;

    int edgecount = 1;
    int edges[100][2];

    //read Edges
    while (!depthFile.atEnd()) {
        QByteArray line = depthFile.readLine();

        int linelength = line.length();

        int cur = 0;

        int _begin = 0 , _end = 0;
        while (cur < linelength) {
            if (line[cur] == ' ') {
                break;
            }
            _begin = _begin * 10 + line[cur] - '0';
            cur ++;
        }

        cur ++;

        while (cur < linelength) {
            if (line[cur] == ' ' || line[cur] == '\n') {
                break;
            }
            _end = _end * 10 + line[cur] - '0';
            cur ++;
        }

        //qDebug() << "edge from " <<  dn[_begin].name << " to " << dn[_end].name;

        edges[edgecount][0] = _begin;
        edges[edgecount][1] = _end;

        edgecount ++;
    }

    //sorted by depth
    sort(dn + 1 , dn + linecount + 1);


    //beforeSortedDepthNode
    int beforeSortedDepthNode[100];

    for (int i = 1 ; i <= linecount ; i ++) {
        for (int j = 1 ; j <= linecount ; j ++) {
            if (i == dn[j].id) {
                beforeSortedDepthNode[i] = j;
                break;
            }
        }
    }

    //sorted depth Node qdebug
    /*for (int i = 1 ; i <= linecount ; i ++) {
        qDebug() << dn[i].name << " " << dn[i].depth;
    }*/

    //draw!
    //set painter and pen
    QPainter paint(this);
    QPen pen;
    pen.setColor(QColor(0 , 0 , 0));
    pen.setWidth(1);
    paint.setPen(pen);

    //draw by depth
    int nowdepth = 0 , nowlinecount = 1;

    int ver = 1;

    //draw text
    while (nowlinecount <= linecount) {
        if (dn[nowlinecount].depth > nowdepth) {
            //print new semester
            nowdepth = dn[nowlinecount].depth;
            QByteArray currsem("第");
            currsem.append(nowdepth + '0');
            currsem.append("学期");


            paint.drawText(QPoint(nowdepth * 100 , 100) , currsem);

            if (nowdepth % 2 == 1) {
                ver = 200;
            }
            else {
                ver = 150;
            }
        }

        paint.drawText(QPoint(nowdepth * 100 , ver) , dn[nowlinecount].name);

        //save coordinate
        dn[nowlinecount].x = nowdepth * 100;
        dn[nowlinecount].y = ver;

        ver += 100;
        nowlinecount ++;
    }

    //draw lines
    edgecount --;
    for (int i = 1 ; i <= edgecount ; i ++) {
        int fromx = dn[beforeSortedDepthNode[edges[i][0]]].x + 15 , fromy = dn[beforeSortedDepthNode[edges[i][0]]].y;
        int tox = dn[beforeSortedDepthNode[edges[i][1]]].x - 15 , toy = dn[beforeSortedDepthNode[edges[i][1]]].y;

        paint.drawLine(fromx , fromy , tox , toy);

        //画箭头
        double arrowlength = 5 , arrowdegree = 0.5;
        double angle = atan2(toy - fromy , tox - fromx) + 3.1415926;

        double x1 , x2 , y1 , y2;
        x1 = tox + arrowlength * cos(angle - arrowdegree);
        y1 = toy + arrowlength * sin(angle - arrowdegree);

        x2 = tox + arrowlength * cos(angle + arrowdegree);
        y2 = toy + arrowlength * sin(angle + arrowdegree);

        paint.drawLine(tox , toy , x1 , y1);
        paint.drawLine(tox , toy , x2 , y2);
    }
}
