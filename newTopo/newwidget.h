#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QWidget>

namespace Ui {
class newwidget;
}

class newwidget : public QWidget
{
    Q_OBJECT

public:
    explicit newwidget(QWidget *parent = nullptr);
    ~newwidget();
    void paintEvent(QPaintEvent *event) override;

signals:
    void back();

private:
    Ui::newwidget *ui;
};

#endif // NEWWIDGET_H
