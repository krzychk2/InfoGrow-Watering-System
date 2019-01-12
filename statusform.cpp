#include "statusform.h"
#include "ui_statusform.h"

StatusForm::StatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusForm)
{
    ui->setupUi(this);

    /*
     * Connect signals from ValveWorker with our update slot
     */

    connect(allValves[0], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[1], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[2], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[3], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[4], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[5], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[6], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);
    connect(allValves[7], &Valve::updateValveTimeSignal, this, &StatusForm::updateValveTimeSlot);


}

StatusForm::~StatusForm()
{
    delete ui;
}

void StatusForm::modifyControls(int timeSec, const HD44780::TimeUnit &timeUnit, QLCDNumber *lcdNumber, QLabel *timeLabel){
    if(timeUnit == HD44780::Minutes)
        timeLabel->setText("m");

    if(timeUnit == HD44780::Seconds)
        timeLabel->setText("s");

    if(timeSec <= 99){
        lcdNumber->display(timeSec);        

    } else {
        lcdNumber->display(static_cast<int>(timeSec/60));
    }
}

void StatusForm::updateValveTimeSlot(const HD44780::Valves &valve, const unsigned int &time, const HD44780::TimeUnit &timeUnit){

    hd44780.updateValveTimeSlot(valve, time, timeUnit);

    switch(valve){
    case HD44780::V1:
            modifyControls(time, timeUnit, ui->lcdNumber_1, ui->timelabel_1);
        break;
    case HD44780::V2:
            modifyControls(time, timeUnit, ui->lcdNumber_2, ui->timelabel_2);
        break;
    case HD44780::V3:
            modifyControls(time, timeUnit, ui->lcdNumber_3, ui->timelabel_3);
        break;
    case HD44780::V4:
            modifyControls(time, timeUnit, ui->lcdNumber_4, ui->timelabel_4);
        break;
    case HD44780::V5:
            modifyControls(time, timeUnit, ui->lcdNumber_5, ui->timelabel_5);
        break;
    case HD44780::V6:
            modifyControls(time, timeUnit, ui->lcdNumber_6, ui->timelabel_6);
        break;
    case HD44780::V7:
            modifyControls(time, timeUnit, ui->lcdNumber_7, ui->timelabel_7);
        break;
    case HD44780::V8:
            modifyControls(time, timeUnit, ui->lcdNumber_8, ui->timelabel_8);
        break;
    }

}

void StatusForm::on_stopAllButton_clicked()
{
    for (const auto &v : allValves){
        v->manualStopValve();
    }
}
