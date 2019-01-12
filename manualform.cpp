#include "manualform.h"
#include "ui_manualform.h"

ManualForm::ManualForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManualForm)
{
    ui->setupUi(this);
}

ManualForm::~ManualForm()
{
    delete ui;
}


void ManualForm::on_okButton_clicked()
{
    /*
     * Run program logic
     */
    unsigned int valveNumber(0);
    if(ui->v1Button->isChecked())
        valveNumber=0;
    if(ui->v2Button->isChecked())
        valveNumber=1;
    if(ui->v3Button->isChecked())
        valveNumber=2;
    if(ui->v4Button->isChecked())
        valveNumber=3;
    if(ui->v5Button->isChecked())
        valveNumber=4;
    if(ui->v6Button->isChecked())
        valveNumber=5;
    if(ui->v7Button->isChecked())
        valveNumber=6;
    if(ui->v8Button->isChecked())
        valveNumber=7;

    allValves.at(valveNumber)->manualStartValve(ui->timeLCDNumber->value());
}

void ManualForm::on_plus1Button_clicked()
{
    if(ui->timeLCDNumber->value() <= 98)
        ui->timeLCDNumber->display(ui->timeLCDNumber->value() + 1);
}

void ManualForm::on_minus1Button_clicked()
{
    if(ui->timeLCDNumber->value() >=1)
        ui->timeLCDNumber->display(ui->timeLCDNumber->value() - 1);
}

void ManualForm::on_plus10Button_clicked()
{
    if(ui->timeLCDNumber->value() <= 88)
        ui->timeLCDNumber->display(ui->timeLCDNumber->value() + 10);
}

void ManualForm::on_minus10Button_clicked()
{
    if(ui->timeLCDNumber->value() >=10)
        ui->timeLCDNumber->display(ui->timeLCDNumber->value() - 10);
}
