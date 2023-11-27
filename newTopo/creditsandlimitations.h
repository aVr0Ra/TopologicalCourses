#ifndef CREDITSANDLIMITATIONS_H
#define CREDITSANDLIMITATIONS_H

#include <QWidget>

namespace Ui {
class CreditsAndLimitations;
}

class CreditsAndLimitations : public QWidget
{
    Q_OBJECT

public:
    explicit CreditsAndLimitations(QWidget *parent = nullptr);
    ~CreditsAndLimitations();

private:
    Ui::CreditsAndLimitations *ui;
};

#endif // CREDITSANDLIMITATIONS_H
