#ifndef STATUSFORM_H
#define STATUSFORM_H

#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include "valve.h"


namespace Ui {
class StatusForm;
}

class StatusForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatusForm(QWidget *parent = 0);
    ~StatusForm();

private:
    Ui::StatusForm *ui;

    void modifyControls(int timeSec, const HD44780::TimeUnit &timeUnit, QLCDNumber *lcdNumber, QLabel *timeLabel);

private slots:
    void updateValveTimeSlot(const HD44780::Valves &valve, const unsigned int &time, const HD44780::TimeUnit &timeUnit);

    void on_stopAllButton_clicked();
};

#endif // STATUSFORM_H
