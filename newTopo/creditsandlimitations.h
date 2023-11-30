#ifndef CREDITSANDLIMITATIONS_H
#define CREDITSANDLIMITATIONS_H

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
class CreditsAndLimitations;
}

class CreditsAndLimitations : public QWidget
{
    Q_OBJECT

signals:
    void back();

public:
    explicit CreditsAndLimitations(QWidget *parent = nullptr);
    ~CreditsAndLimitations();

private:
    Ui::CreditsAndLimitations *ui;
};

#endif // CREDITSANDLIMITATIONS_H
