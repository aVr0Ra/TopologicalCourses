#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>

namespace Ui {
class schedule;
}

class schedule : public QWidget
{
    Q_OBJECT

signals:
    void back();

public:
    explicit schedule(QWidget *parent = nullptr);
    ~schedule();

private:
    Ui::schedule *ui;
};

#endif // SCHEDULE_H
