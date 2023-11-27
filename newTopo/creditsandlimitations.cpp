#include "creditsandlimitations.h"
#include "ui_creditsandlimitations.h"

CreditsAndLimitations::CreditsAndLimitations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditsAndLimitations)
{
    ui->setupUi(this);
}

CreditsAndLimitations::~CreditsAndLimitations()
{
    delete ui;
}
