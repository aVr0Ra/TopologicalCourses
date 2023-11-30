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


    QString CSVschedule[10][10][10];

    this->setFixedSize(1920 , 1080);
    this->setWindowTitle("查看预设课程表");

    //setting layout
    QGridLayout *layout = new QGridLayout(this);


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

    //qDebug() << "linecount = " << linecount;

    depthFile.close();

    //depth debug
/*
    for (int i = 1 ; i <= linecount ; i ++) {
        qDebug() << dn[i].name << " " << dn[i].depth;
    }
*/
    sort(dn + 1 , dn + linecount + 1 , cmp);

    int nodecount = linecount;

    int gridrow = 0 , gridcolumn = 0;

    string numbers[9] = {"" , "一" , "二" , "三" , "四" , "五" , "六" , "七" , "八"};

    QStringList vheaders;
    vheaders << "1+2" << "3+4" << "5+6" << "7+8" << "9+10" << "11+12";
    QStringList hheaders;
    hheaders << "一" << "二" << "三" << "四" << "五" << "六" << "日";

    // making table

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
        tableWidget->setRowCount(6); // 设置行数
        tableWidget->setColumnCount(7); // 设置列数


        tableWidget->setHorizontalHeaderLabels(hheaders);
        tableWidget->setVerticalHeaderLabels(vheaders);

        for (int j = 0 ; j < 6 ; j ++) {
            tableWidget->setRowHeight(j , 50);
        }

        for (int j = 0 ; j < 7 ; j ++) {
            tableWidget->setColumnWidth(j , 83);
        }

        // 添加项目到表格
        // tableWidget->setItem(0, 1, new QTableWidgetItem("Item 2"));

        int curDepthCourseCount = 0;


        for (int node = 1 ; node <= nodecount ; node ++) {
            if (dn[node].depth == i) {
                tableWidget->setItem(mapx[curDepthCourseCount] - 1 , mapy[curDepthCourseCount] - 1 ,
                                     new QTableWidgetItem(dn[node].name));

                CSVschedule[i][mapx[curDepthCourseCount] - 1][mapy[curDepthCourseCount] - 1] = dn[node].name;

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


    //last grid with 2 buttons
    QPushButton *ret = new QPushButton("不保存以上课表，直接返回");
    QPushButton *savecsv = new QPushButton("保存以上课表CSV文件并返回");
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    ret->setFixedSize(200, 50);
    savecsv->setFixedSize(200, 50);

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addStretch();
    hLayout1->addWidget(ret);
    hLayout1->addStretch();

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addStretch();
    hLayout2->addWidget(savecsv);
    hLayout2->addStretch();

    verticalLayout->addStretch();
    verticalLayout->addLayout(hLayout1);
    verticalLayout->addLayout(hLayout2);
    verticalLayout->addStretch();

    layout->addLayout(verticalLayout, 2, 2);

    //set layout

    this->setLayout(layout);


    //ret button
    connect(ret, &QPushButton::clicked, [=](){
        emit this->back();
    });

    //save button
    connect(savecsv , &QPushButton::clicked , [this , CSVschedule , numbers](){
        QStringList vheaders;
        vheaders << "1+2" << "3+4" << "5+6" << "7+8" << "9+10" << "11+12";
        QStringList hheaders;
        hheaders << "" <<  "一" << "二" << "三" << "四" << "五" << "六" << "日";

        QString fileName;

        while (true) {
            fileName = QFileDialog::getSaveFileName(this, "保存文件", "", "CSV 文件 (*.csv)");
            if (fileName.isEmpty()) {
                return;
            }

            if (QFileInfo::exists(fileName)) {
                int ret = QMessageBox::warning(this, "文件已存在",
                                       "指定的文件已存在。您要覆盖它吗？",
                                               QMessageBox::Yes | QMessageBox::No);

                if (ret == QMessageBox::Yes) {
                    break;
                }
            }
            else break;
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            const char utf8bom[] = { char(0xEF), char(0xBB), char(0xBF) };
            file.write(utf8bom, sizeof(utf8bom));

            //QStringList data = {"Name,Score,Date", "Alice,90,2021-01-01", "Bob,85,2021-01-02"};

            QStringList data;

            for (int i = 1 ; i <= 8 ; i ++) {
                // 第 x 学期课表
                QString qslabel = "";
                qslabel.append("第");
                qslabel.append(numbers[i]);
                qslabel.append("学期课表");
                data.append(qslabel);

                // 一~日
                QString curHHeader = hheaders.join(",");
                data.append(curHHeader);

                for (int j = 0 ; j < 6 ; j ++) {
                    QStringList curLineList;
                    curLineList.append(vheaders[j]);

                    for (int k = 0 ; k < 7 ; k ++) {
                        curLineList.append(CSVschedule[i][j][k]);
                    }

                    QString curLine = curLineList.join(",");
                    data.append(curLine);
                }

                data.append("\n");
            }

            foreach (const QString &line, data) {
                stream << line << "\n";
            }

            file.close();
        }
        else {
            QMessageBox::warning(this, "错误", "无法打开文件进行写入。");
        }

        QMessageBox::information(this, "保存成功", "文件已成功保存！");

        emit this->back();
    });
}

schedule::~schedule()
{
    delete ui;
}
